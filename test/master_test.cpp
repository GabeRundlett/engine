#include <coel/coel.hpp>
#include <debug/debug.hpp>

int main() {
    DEBUG_PROFILE_SESSION(master_test, "engine_prof.json");
    auto window = coel::create_window(800, 800, "test");
    if (!window) return -1;

    float vertices[] = {-0.5, -0.5, 0.0, 0.5, 0.5, -0.5};
    auto vbo = coel::create_vbo(vertices, sizeof(vertices), {{coel::Type::f32, 2}});

    unsigned short indices[] = {0, 1, 2};
    auto ibo = coel::create_ibo(indices, sizeof(indices));

    auto vao = coel::create_vao();
    vao->add_vbo(vbo);

    while (!window->should_close()) {
        coel::Renderer::clear();
        vao->draw(ibo);
        window->update();
    }

    window->close();
    return 0;
}
