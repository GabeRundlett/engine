#include <Coel.hpp>

int main() {
    Coel::Window window;
    Coel::create(window);

    Coel::Vao vao{};
    Coel::Vbo vbo{{{Coel::F32, 3}, {Coel::F32, 2}}};
    Coel::Ibo ibo{};

    Coel::create(vbo, nullptr, 1024);
    Coel::create(ibo, nullptr, 1024);
    Coel::create(vao);
    Coel::link(vao, vbo);

    Coel::destroy(ibo);
    Coel::destroy(vbo);
    Coel::destroy(vao);

    Coel::destroy(window);
}
