#include <coel.hpp>
#include <math.hpp>

namespace test {
    static constexpr char vert_src[] = R"(
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

    static constexpr char frag_src[] = R"(
#version 330 core
in vec2 v_tex;
in vec4 v_col;
in float v_tid;
uniform sampler2D tex0;
uniform sampler2D tex1;
out vec4 color;
void main() {
	switch (int(v_tid + 0.5 * sign(v_tid))) {
	case -1: color = v_col; break;
	case 0: color = texture(tex0, v_tex); break;
	case 1: color = texture(tex1, v_tex); break;
	default: color = vec4(ivec3(gl_FragCoord.x + gl_FragCoord.y) / 50 % 2, 1);
	}
}
)";

    /*struct Window : coel::Window {
           math::Vec2 mouse, size;

           Window(const unsigned int width, const unsigned int height, const char *const title)
               : coel::Window(width, height, title), mouse{0, 0}, size{float(width), float(height)} {}

           void mouse_move(const coel::MouseMove &e) override { mouse = {float(e.x), size.y - float(e.y)}; }
           void window_resize(const coel::WindowResize &e) override { size = {float(e.width), float(e.height)}; }
       };*/
} // namespace test

int main() {
    coel::Window window(800, 800, "window");

    coel::Texture ball_t("assets/player.png");
    coel::Texture dirt_t("assets/ground.png");
    coel::Shader shader(test::vert_src, test::frag_src);
    coel::Material material(&shader, &ball_t, "tex0", &dirt_t, "tex1");

    coel::renderer::batch2d::init();

    math::Vec2 pos = {-0.5, -0.3}, vel = {0.221, 0.057};

    float prev_time = window.get_time();

    while (!window.should_close()) {
        coel::renderer::clear(0.3, 0.3, 0.3, 1);

        coel::renderer::batch2d::submit_rect(-1, -1, 2, 2, 1);
        coel::renderer::batch2d::submit_rect(pos.x, pos.y, 1, 1, 0.f);
        coel::renderer::batch2d::flush();

        const float time = window.get_time(), elapsed = time - prev_time;
        prev_time = time;

        pos += vel * elapsed;

        if (pos.x > 0.f) {
            vel.x *= -1;
            pos.x = 0.f;
        } else if (pos.x < -1.f) {
            vel.x *= -1;
            pos.x = -1.f;
        }

        if (pos.y > 0.f) {
            vel.y *= -1;
            pos.y = 0.f;
        } else if (pos.y < -1.f) {
            vel.y *= -1;
            pos.y = -1.f;
        }

        window.update();
    }
}
// hi honey i love you !
