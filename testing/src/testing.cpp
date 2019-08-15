#include "shader_src.hpp"
#include <coel.hpp>

static float cam_pos[] = {0, 0};
static float window_size[] = {640, 640};

void window_resize(const coel::window::Resize &e) {
    window_size[0] = e.width;
    window_size[1] = e.height;
}

int main() {
    coel::window::callback::set::window::resize(window_resize);

    coel::Window window = coel::window::create(window_size[0], window_size[1], "Window");
    coel::Shader shader = coel::renderer::shader::create(s_vert_src, s_frag_src);
    coel::Texture texture = coel::renderer::texture::create("player.png");

    coel::renderer::batch::init();

    while (coel::window::update(&window)) {
        coel::renderer::clear(0.5, 0.5, 0.9, 1.0);
        coel::renderer::shader::send_vec2(&shader, "screen_size", window_size);
        coel::renderer::shader::send_vec2(&shader, "cam_pos", cam_pos);

        coel::renderer::batch::begin(&shader);
        coel::renderer::batch::submit(0, 0, window_size[0], window_size[1], &texture);
        coel::renderer::batch::end();
    }
}

/*
#include "shader_src.hpp"
#include <coel.hpp>

#include <iostream>
#include <vector>

static coel::Window window;
static coel::Shader shader;

constexpr static double    //
    move_speed = 2000,     //
    jump_speed = 400,      //
    air_friction = 0,      //
    ground_friction = 0.5, //
    mid_air_slowdown = 1,  //
    gravity_speed = 800;   //

constexpr static unsigned short    //
    pause_key = coel::key::Escape, //
    jump_key = coel::key::W,       //
    down_key = coel::key::S,       //
    left_key = coel::key::A,       //
    right_key = coel::key::D;      //

static constexpr unsigned int chunk_size = 600;

// Ordered as follows: Is on ground, none, none, none, Up, Down, Left, Right
static unsigned char keys = 0b00000000;

static bool active = false;
static float mouse[] = {0, 0};
static float screen_res[] = {1600, 900};

struct Player {
    float pos_x, pos_y, vel_x, vel_y, w, h;
};
struct Camera {
    float x, y;
};
static Player player = {100, 200, 0, 0, 32, 32};
static Camera cam = {0, -150};

void window_size(const coel::window::Resize &e) {
    screen_res[0] = (float)e.width;
    screen_res[1] = (float)e.height;
}
void key_press(const coel::key::Press &e) {
    if (e.key == jump_key) keys |= 0x8;
    if (e.key == down_key) keys |= 0x4;
    if (e.key == left_key) keys |= 0x2;
    if (e.key == right_key) keys |= 0x1;
    if (e.key == pause_key) {
        coel::window::set_cursor_visibility(&window, true);
        keys &= 0x7F;
    }
}
void key_release(const coel::key::Release &e) {
    if (e.key == jump_key) keys &= 0xF7;
    if (e.key == down_key) keys &= 0xFB;
    if (e.key == left_key) keys &= 0xFD;
    if (e.key == right_key) keys &= 0xFE;
}
void mouse_move(const coel::mouse::Move &e) {
    mouse[0] = (float)e.x;
    mouse[1] = (float)e.y;
}
void mouse_press(const coel::mouse::Press &e) {
    mouse[0] = screen_res[0] / 2;
    mouse[1] = screen_res[1] / 2;
    coel::window::set_cursor_pos(&window, screen_res[0] / 2, screen_res[1] / 2);
    coel::window::set_cursor_visibility(&window, false);
    keys |= 0x80;
}

struct Box {
    float x, y, w, h;
};
struct Chunk {
    std::vector<Box> boxes;
};
static Chunk world = {{
    {500, 0, 200, 50},
    {800, 75, 200, 50},
    {400, 150, 200, 50},
}};

// static Chunk world[3 * 3] = {
//    {{}},
//    {{{0, 0, 200, 50}}},
//    {{}},
//    //
//    {{}},
//    {{}},
//    {{}},
//    //
//    {{}},
//    {{}},
//    {{}},
//};

int main() {
    coel::window::callback::set::window::resize(window_size);
    coel::window::callback::set::key::press(key_press);
    coel::window::callback::set::key::release(key_release);
    coel::window::callback::set::mouse::press(mouse_press);
    coel::window::callback::set::mouse::move(mouse_move);

    window = coel::window::create(screen_res[0], screen_res[1], "test window");
    shader = coel::renderer::shader::create(s_vert_src, s_frag_src);
    coel::Texture player_texture = coel::renderer::texture::create("player.png");
    // coel::Texture ground_texture = coel::renderer::texture::create("ground.png");
    coel::renderer::batch::init();
    double prev_time = 0.0;

    while (coel::window::update(&window)) {
        const double time = coel::window::get_time(), elapsed = time - prev_time;
        prev_time = time;

        coel::renderer::clear(0.4, 0.4, 0.9, 1);

        coel::renderer::shader::send_vec3(&shader, "mouse_pos", mouse);
        coel::renderer::shader::send_vec2(&shader, "screen_size", screen_res);
        coel::renderer::shader::send_vec2(&shader, "cam_pos", reinterpret_cast<float *>(&cam));
        coel::renderer::shader::send_float(&shader, "time", static_cast<float>(time));

        coel::renderer::batch::begin(&shader);
        coel::renderer::batch::submit(0, -1000, screen_res[0], 1000, nullptr);
        for (Box box : world.boxes)
            coel::renderer::batch::submit(box.x, box.y, box.w, box.h, nullptr);

        if (keys & 0x80) {
            coel::window::set_cursor_pos(&window, screen_res[0] / 2, screen_res[1] / 2);

            player.vel_y *= 1.0 - elapsed * air_friction;        // apply "friction"
            if (keys & 0x40) {                                   // is on a surface
                player.vel_x *= 1.0 - elapsed * ground_friction; // apply "friction"
                if (keys & 0x8) {
                    player.vel_y = jump_speed;
                    keys &= 0xBF;
                }
                // if (keys & 0x4) player.vel_y -= speed / 250;
                if (keys & 0x2) player.vel_x -= move_speed * elapsed; // speed up left
                if (keys & 0x1) player.vel_x += move_speed * elapsed; // speed up right
            }
            if (keys & 0x2) {
                if (player.vel_x > 0.f) player.vel_x *= 1.0 - elapsed * mid_air_slowdown; // slow left mid air
            }
            if (keys & 0x1) {
                if (player.vel_x < 0.f) player.vel_x *= 1.0 - elapsed * mid_air_slowdown; // speed up right
            }
            player.vel_y -= gravity_speed * elapsed; // gravity
            player.pos_y += player.vel_y * elapsed;  // move x
            player.pos_x += player.vel_x * elapsed;  // move y

            // if the player is underground
            if (player.pos_y < 0) {
                player.pos_y = 0;
                player.vel_y = 0;
                keys |= 0x40;
            }

            // if the player is to the side
            if (player.pos_x < 0) {
                player.pos_x = 0;
                player.vel_x = 0;
            } else if (player.pos_x + player.w > screen_res[0]) {
                player.pos_x = screen_res[0] - player.w;
                player.vel_x = 0;
            }

            // if the player is inside a box
            for (Box box : world.boxes) {
                if (player.pos_x + player.w > box.x && player.pos_x < box.x + box.w && //
                    player.pos_y + player.h > box.y && player.pos_y < box.y + box.h) { //

                    const float vel_slope = player.vel_y / player.vel_x;
                    float diffx = 0.f, diffy = 0.f;
                    unsigned char side = 0;

                    if (player.vel_x < 0.f) {
                        float y_int = (box.x + box.w - player.pos_x) * vel_slope + player.pos_y;
                        if (player.vel_y < 0.f) { // either 2 or 4 (right top)
                            if (y_int > box.y + box.h)
                                side = 4;
                            else
                                side = 2;
                        } else if (player.vel_y > 0.f) { // either 2 or 3 (right bottom)
                            if (y_int < box.y - player.h)
                                side = 3;
                            else
                                side = 2;
                        } else {
                            side = 2;
                        }
                    } else if (player.vel_x > 0.f) {
                        if (player.vel_y < 0.f) { // either 1 or 4 (left top)
                            float y_int = (box.x - player.pos_x - player.w) * vel_slope + player.pos_y;
                            if (y_int > box.y + box.h)
                                side = 4;
                            else
                                side = 1;
                        } else if (player.vel_y > 0.f) { // either 1 or 3 (left bottom)
                            float y_int = (box.x - player.pos_x) * vel_slope + player.pos_y;
                            if (y_int < box.y)
                                side = 3;
                            else
                                side = 1;
                        } else {
                            side = 1;
                        }
                    } else {
                        if (player.vel_y < 0.f)
                            side = 4;
                        else if (player.vel_y > 0.f)
                            side = 3;
                    }

                    switch (side) {
                    case 1: // Move to left
                        diffx = box.x - player.pos_x - player.w;
                        player.vel_x *= -0.9f;
                        break;
                    case 2: // Move to right
                        diffx = box.x - player.pos_x + box.w;
                        player.vel_x *= -0.9f;
                        break;
                    case 3: // Move to bottom
                        diffy = box.y - player.pos_y - player.h;
                        player.vel_y *= -0.9f;
                        break;
                    case 4: // Move to top
                        diffy = box.y - player.pos_y + box.h;
                        player.vel_y = 0.0f;
                        keys |= 0x40;
                        break;
                    default: break;
                    }

                    player.pos_x += diffx;
                    player.pos_y += diffy;
                }
            }
        }

        coel::renderer::batch::submit(player.pos_x, player.pos_y, player.w, player.h, nullptr);
        coel::renderer::batch::end();
    }
}
*/
