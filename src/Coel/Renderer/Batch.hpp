#pragma once

#include <Coel/Renderer/Buffer.hpp>
#include <Coel/Renderer/Shader.hpp>

namespace Coel { namespace Renderer {
    struct Batch {
        Vao vao{};
        Vbo vbo;
        Ibo ibo{};
        Shader shader;

        Batch(const Layout &l, const char *const vertSrc, const char *const fragSrc);
    };

    void init(Batch &b, const unsigned int vsize, const unsigned int isize);
    void deinit(Batch &b);
}} // namespace Coel::Renderer
