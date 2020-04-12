#pragma once

#include <Coel/Renderer/Buffer.hpp>
#include <Coel/Renderer/Shader.hpp>

namespace Coel { namespace Renderer {
    struct Batch {
        Vao vao{};
        Vbo vbo;
        Ibo ibo{};

        Batch(const Layout &l);
    };

    void init(Batch &b, const uint32_t vsize, const uint32_t isize);
    void deinit(Batch &b);
}} // namespace Coel::Renderer
