#include <coel.hpp>

struct MyWindow : coel::Window {
    MyWindow(const unsigned int width, const unsigned int height, const char *const title)
        : coel::Window(width, height, title) {}
};

int main() {
    MyWindow window(800, 600, "window_title");

    coel::Shader shader_1("vert_shader_source", "frag_shader_source");
    coel::Texture texture_1("png_filepath");
    coel::Texture texture_2("png_filepath");

    coel::KeyPress;
    coel::KeyCode::A;

    float model_1_pos_data[] = {-0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5, 0.5};
    unsigned short model_1_ind_data[] = {0, 1, 2, 1, 3, 2};
    coel::Model model_1(model_1_pos_data, model_1_ind_data); // custom models need layouts
    coel::Material material_1(&shader_1, &texture_1);

    coel::Model model_2("obj_filepath");
    coel::Material material_2(&shader_1, &texture_2);

    coel::Renderable player_r(&model_1, &material_1);
    coel::Renderable ground_r(&model_2, &material_2);

    while (window.update()) {
        coel::renderer::clear(0x000000ff);

        coel::renderer::submit(&player_r);
        coel::renderer::submit(&ground_r);

        coel::renderer::flush();
    }
}
