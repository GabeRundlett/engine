#pragma once

#include <Coel/Renderer/Batch.hpp>

namespace Coel { namespace Renderer {

    struct Batch3d {
        struct Vertex {
            glm::vec3 pos;
            glm::vec2 tex;
        };
        struct Tri {
            Vertex a, b, c;
        };
        struct Quad {
            Vertex a, b, c, d;
        };

        Batch batch{{{F32, 3}, {F32, 2}}};

        void begin();
        void flush();

        void submitTri(const Tri &tri);
        void submitQuad(const Quad &quad);

        Vertex *vhandle{};
        unsigned int *ihandle{};
        unsigned int vcount{}, icount{};
    };

    void init(Batch3d &b);
    void deinit(Batch3d &b);
}} // namespace Coel::Renderer
