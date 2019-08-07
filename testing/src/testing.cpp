#include "shader_src.hpp"
#define COEL_SET_DEFAULT_WINDOW_API_GLFW
#define COEL_SET_DEFAULT_RENDERER_API_OPENGL
#include <coel.hpp>

#include <iostream>

int main() {
    coel::Window window = coel::window::create(800, 720, "test window");
    coel::Shader shader = coel::renderer::shader::create(s_vert_src, s_frag_src);
    coel::renderer::shader::bind(&shader);

    static constexpr float pos_data[] = {-0.8, -0.8, 0.8, -0.8, -0.8, 0.8, 0.8, 0.8};
    static constexpr float col_data[] = {0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0};
    static constexpr unsigned short index_data[] = {0, 1, 2, 1, 3, 2};

    coel::renderer::vbo::create(pos_data, 2 * sizeof(float), 4);
    coel::renderer::vbo::create(col_data, 3 * sizeof(float), 4);
    coel::IBO ibo = coel::renderer::ibo::create(index_data, 6);

    double prev_time = 0.0;
    double total_time = 0.0;
    unsigned long long total_frames = 1;

    while (coel::window::update(&window)) {
        coel::renderer::clear(0.0, 0.0, 0.0, 1.0);
        coel::renderer::draw_buffers(&ibo);

        double time = coel::window::get_time();
        total_time += time - prev_time;
        std::cout << "average frame time " << total_time / total_frames << ", average fps " << 1.0 / (total_time / total_frames)
                  << ", frame time " << time - prev_time << ", fps: " << 1.0 / (time - prev_time) << '\n';
        prev_time = time;
        ++total_frames;
    }
}
