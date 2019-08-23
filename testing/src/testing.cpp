#include <coel.hpp>
#include <math.hpp>

constexpr char vert_src[] = R"(
#version 330 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 tex;
layout(location = 2) in vec4 col;
layout(location = 3) in float tid;
out vec2 v_tex;
out vec4 v_col;
out float v_tid;
void main() {
	v_tex = tex;
	v_col = col / 255;
	v_tid = tid;
    gl_Position = vec4(pos, 0, 1);
}
)";

constexpr char frag_src[] = R"(
#version 330 core
in vec2 v_tex;
in vec4 v_col;
in float v_tid;
uniform sampler2D tex1;
uniform sampler2D tex2;
out vec4 color;
void main() {
	switch (int(v_tid + 0.5 * sign(v_tid))) {
	case -1: color = v_col; break;
	case 0: color = texture(tex1, v_tex); break;
	case 1: color = texture(tex2, v_tex); break;
	case 2: 
		if (abs(v_tex.x - v_tex.y) < 0.1)
			color = vec4(0, 0, 0, 1);
		else
			color = vec4(0);
		break;
	default: color = vec4(1, 0, 1, 1); break;
	}
}
)";

struct Vertex {
    math::Vec2 pos, tex;
    math::Color col;
    float tid;
};

struct TestWindow : coel::Window {
    math::Vec2 mouse, size;

    TestWindow(const unsigned int width, const unsigned int height, const char *const title)
        : coel::Window(width, height, title), mouse{0, 0}, size{float(width), float(height)} {}

    void mouse_move(const coel::MouseMove &e) override { mouse = {float(e.x) / size.x * 2 - 1, 1 - float(e.y) / size.y * 2}; }
    void window_resize(const coel::WindowResize &e) override { size = {float(e.width), float(e.height)}; }
};

struct Rectangle {
    Vertex vertices[4];
    static constexpr unsigned short indices[] = {0, 1, 2, 1, 3, 2};
    coel::Model model = coel::Model(vertices, sizeof(vertices), indices, sizeof(indices));
    Rectangle(const math::Vec2 &pos, const math::Vec2 &size, const float tex_slot = -1)
        : vertices{
              {{pos.x, pos.y}, {0.f, 0.f}, {0, 0, 0, 255}, tex_slot},                   //
              {{pos.x, pos.y + size.y}, {0.f, 1.f}, {0, 0, 0, 255}, tex_slot},          //
              {{pos.x + size.x, pos.y}, {1.f, 0.f}, {0, 0, 0, 255}, tex_slot},          //
              {{pos.x + size.x, pos.y + size.y}, {1.f, 1.f}, {0, 0, 0, 255}, tex_slot}, //
          } {}
    Rectangle(const math::Vec2 &pos, const math::Vec2 &size, const math::Color &color)
        : vertices{
              {{pos.x, pos.y}, {0.f, 0.f}, color, -1},                   //
              {{pos.x, pos.y + size.y}, {0.f, 1.f}, color, -1},          //
              {{pos.x + size.x, pos.y}, {1.f, 0.f}, color, -1},          //
              {{pos.x + size.x, pos.y + size.y}, {1.f, 1.f}, color, -1}, //
          } {}
    inline void set_pos(const math::Vec2 &pos) {
        const math::Vec2 offset = pos - vertices[0].pos;
        for (unsigned char i = 0; i < 4; ++i)
            vertices[i].pos += offset;
    }
    inline void set_size(const math::Vec2 &size) {
        const math::Vec2 pos = vertices[0].pos;
        vertices[0].pos = pos;
        vertices[1].pos = {pos.x, pos.y + size.y};
        vertices[2].pos = {pos.x + size.x, pos.y};
        vertices[3].pos = pos + size;
    }
};

int main() {
    TestWindow window(800, 800, "window");
    coel::Shader shader(vert_src, frag_src);

    Rectangle ball({-0.8, -0.6}, {0.6, 1.2}, 0);
    coel::Texture ball_t("assets/player.png");

    Rectangle dirt({0.2, -0.6}, {0.6, 1.2}, 1);
    coel::Texture dirt_t("assets/ground.png");

    Rectangle box({0, 0}, {0.8, 0.8}, 2);

    coel::Material material(&shader, &ball_t, "tex1", &dirt_t, "tex2");
    coel::renderer::layout(coel::LayoutType::Float, 2, coel::LayoutType::Float, 2, coel::LayoutType::UByte, 4,
                           coel::LayoutType::Float, 1);

    while (window.update()) {
        const float time = window.get_time();
        box.set_pos(window.mouse);
        box.set_size({math::sin(time), math::cos(time)});

        coel::renderer::clear();
        coel::renderer::submit(&box.model);
        // coel::renderer::submit(&dirt.model);
        // coel::renderer::submit(&ball.model);
        coel::renderer::flush();
    }
}
