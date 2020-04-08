#pragma once

#include <Coel/Renderer/Buffer.hpp>

namespace Coel { namespace Renderer {
    class Quad2d {
        Vao m_vao{};
        Vbo m_vbo{{{F32, 2}, {F32, 2}}};
        Ibo m_ibo{};

      public:
        Quad2d();
        void draw();
    };
}} // namespace Coel::Renderer
