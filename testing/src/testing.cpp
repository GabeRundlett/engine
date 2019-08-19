#include <coel.hpp>

constexpr char vert_src[] = R"(
#version 330 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 tex;
out vec2 v_tex;
void main() {
	v_tex = tex;
    gl_Position = vec4(pos, 0, 1);
}
)";

constexpr char frag_src[] = R"(
#version 330 core
in vec2 v_tex;
uniform sampler2D tex;
out vec4 color;
void main() {
	color = texture(tex, v_tex);
}
)";

int main() {
    coel::Window window(800, 800, "window");
    float vdata[] = {
        -1.0, -1.0, 0.0, 0.0, //
        -1.0, 1.0,  0.0, 1.0, //
        1.0,  -1.0, 1.0, 0.0, //
        1.0,  1.0,  1.0, 1.0, //
    };
    unsigned short idata[] = {0, 1, 2, 1, 3, 2};
    coel::Model model(vdata, sizeof(vdata), idata, sizeof(idata));
    coel::Shader shader(vert_src, frag_src);
    coel::Texture texture("assets/player.png");
    coel::Material material(&shader, &texture);
    coel::Renderable sprite(&model, &material);
    coel::renderer::layout(coel::LayoutType::Float, 2, coel::LayoutType::Float, 2);
    while (window.update()) {
        coel::renderer::clear();
        coel::renderer::submit(&sprite);
        coel::renderer::flush();
    }
}
