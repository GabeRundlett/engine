#include "shader_src.hpp"
#include <coel.hpp>

#include <cmath>
#include <iostream>
#include <vector>

static coel::Window window;
static coel::Shader shader;

constexpr static double speed = 500, sensitivity = 0.00075f;

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

static Player player = {100, 200, 0, 0, 25, 25};
static Camera cam = {0, -150};

void window_size(const coel::window::Resize &e) {
    screen_res[0] = (float)e.width;
    screen_res[1] = (float)e.height;
}
void key_press(const coel::key::Press &e) {
    if (e.key == coel::key::W) keys |= 0x8;
    if (e.key == coel::key::S) keys |= 0x4;
    if (e.key == coel::key::A) keys |= 0x2;
    if (e.key == coel::key::D) keys |= 0x1;
    if (e.key == coel::key::Escape) {
        coel::window::set_cursor_visibility(&window, true);
        keys &= 0x7F;
    }
}
void key_release(const coel::key::Release &e) {
    if (e.key == coel::key::W) keys &= 0xF7;
    if (e.key == coel::key::S) keys &= 0xFB;
    if (e.key == coel::key::A) keys &= 0xFD;
    if (e.key == coel::key::D) keys &= 0xFE;
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

static constexpr unsigned int chunk_size = 600;

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
        coel::renderer::batch::submit(0, -1000, screen_res[0], 1000);
        for (Box box : world.boxes) {
            coel::renderer::batch::submit(box.x, box.y, box.w, box.h);
        }

        if (keys & 0x80) {
            coel::window::set_cursor_pos(&window, screen_res[0] / 2, screen_res[1] / 2);

            player.vel_y *= 1.0 - elapsed / 5;     // apply "friction"
            if (keys & 0x40) {                     // is on a surface
                player.vel_x *= 1.0 - elapsed * 4; // apply "friction"
                if (keys & 0x8) {
                    player.vel_y = speed * 1.6;
                    keys &= 0xBF;
                }
                // if (keys & 0x4) player.vel_y -= speed / 250;
                if (keys & 0x2) player.vel_x -= speed / 300; // speed up left
                if (keys & 0x1) player.vel_x += speed / 300; // speed up right
            }
            if (keys & 0x2) {
                if (player.vel_x > 0.f) player.vel_x *= 1.0 - elapsed * 8; // slow left mid air
            }
            if (keys & 0x1) {
                if (player.vel_x < 0.f) player.vel_x += speed / 300; // speed up right
            }
            player.vel_y -= speed * elapsed * 5;    // gravity
            player.pos_y += player.vel_y * elapsed; // move x
            player.pos_x += player.vel_x * elapsed; // move y

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
                            if (y_int < box.y)
                                side = 3;
                            else
                                side = 2;
                        } else {
                            side = 2;
                        }
                    } else if (player.vel_x > 0.f) {
                        float y_int = (box.x - player.pos_x) * vel_slope + player.pos_y;
                        if (player.vel_y < 0.f) { // either 1 or 4 (left top)
                            if (y_int > box.y + box.h)
                                side = 4;
                            else
                                side = 1;
                        } else if (player.vel_y > 0.f) { // either 1 or 3 (left bottom)
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

        coel::renderer::batch::submit(player.pos_x, player.pos_y, player.w, player.h);
        coel::renderer::batch::end();
    }
}
