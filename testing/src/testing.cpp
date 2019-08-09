#include "shader_src.hpp"
#define COEL_SET_DEFAULT_WINDOW_API_GLFW
#define COEL_SET_DEFAULT_RENDERER_API_OPENGL
#include <coel.hpp>

#include <cmath>
#include <iostream>

static coel::Window window;
static coel::Shader shader;

static bool keyA = false, keyD = false, keyW = false, keyS = false;
static bool keySpace = false, keyLShift = false, active = false;
constexpr static double speed = 150, sensitivity = 0.00075f;
static float mouse[] = {0, 0};
static float screen_res[] = {1600, 900};
static float player_pos[] = {100, 100};

void window_size(const coel::window::Resize &e) {
    screen_res[0] = (float)e.width;
    screen_res[1] = (float)e.height;
}
void key_press(const coel::key::Press &e) {
    if (e.key == coel::key::W)
        keyW = true;
    if (e.key == coel::key::S)
        keyS = true;
    if (e.key == coel::key::A)
        keyA = true;
    if (e.key == coel::key::D)
        keyD = true;
    if (e.key == coel::key::Space)
        keySpace = true;
    if (e.key == coel::key::LeftShift)
        keyLShift = true;
    if (e.key == coel::key::Escape) {
        coel::window::set_cursor_visibility(&window, true);
        active = false;
    }
}
void key_release(const coel::key::Release &e) {
    if (e.key == coel::key::W)
        keyW = false;
    if (e.key == coel::key::S)
        keyS = false;
    if (e.key == coel::key::A)
        keyA = false;
    if (e.key == coel::key::D)
        keyD = false;
    if (e.key == coel::key::Space)
        keySpace = false;
    if (e.key == coel::key::LeftShift)
        keyLShift = false;
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
    active = true;
}

int main() {
    coel::window::callback::set::window::resize(window_size);
    coel::window::callback::set::key::press(key_press);
    coel::window::callback::set::key::release(key_release);
    coel::window::callback::set::mouse::move(mouse_move);
    coel::window::callback::set::mouse::press(mouse_press);

    window = coel::window::create(screen_res[0], screen_res[1], "test window");
    shader = coel::renderer::shader::create(s_vert_src, s_frag_src);
    coel::renderer::shader::bind(&shader);

    static constexpr float pos_data[] = {-1, -1, 1, -1, -1, 1, 1, 1};
    static constexpr float tex_data[] = {0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0};
    static constexpr unsigned short index_data[] = {0, 1, 2, 1, 3, 2};

    coel::renderer::vbo::create(pos_data, 2, 4);
    coel::renderer::vbo::create(tex_data, 3, 4);
    coel::IBO ibo = coel::renderer::ibo::create(index_data, 6);

    double prev_time = 0.0;

    while (coel::window::update(&window)) {
        double time = coel::window::get_time(), elapsed = time - prev_time;

        coel::renderer::clear(0.0, 0.0, 0.0, 1.0);
        coel::renderer::draw_buffers(&ibo);

        coel::window::_internal::glfw::get_time();

        coel::renderer::shader::send_vec3(&shader, "mouse_pos", mouse);
        coel::renderer::shader::send_vec2(&shader, "screen_size", screen_res);
        coel::renderer::shader::send_vec2(&shader, "player_pos", player_pos);
        coel::renderer::shader::send_float(&shader, "time", static_cast<float>(time));

        if (active) {
            coel::window::set_cursor_pos(&window, screen_res[0] / 2, screen_res[1] / 2);
            if (keyW)
                player_pos[1] += speed * elapsed;
            if (keyS)
                player_pos[1] -= speed * elapsed;
            if (keyA)
                player_pos[0] -= speed * elapsed;
            if (keyD)
                player_pos[0] += speed * elapsed;
        }

        prev_time = time;
    }
}
