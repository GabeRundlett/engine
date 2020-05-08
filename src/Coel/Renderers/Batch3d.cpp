#include "Batch3d.hpp"
#include "../Renderer/Renderer.hpp"

namespace Coel { namespace Renderer {
    constexpr unsigned int QUAD_COUNT = 10000, VCOUNT = QUAD_COUNT * 4, ICOUNT = QUAD_COUNT * 6,
                           VSIZE = VCOUNT * sizeof(Batch3d::Vertex), ISIZE = ICOUNT * sizeof(unsigned int);

    void init(Batch3d &b) {
        init(b.batch, VSIZE, ISIZE); //
    }

    void deinit(Batch3d &b) {
        deinit(b.batch); //
    }

    void Batch3d::begin() {
        Coel::open(batch.vbo, &vhandle);
        Coel::open(batch.ibo, &ihandle);
    }

    void Batch3d::flush() {
        Coel::close(batch.vbo);
        Coel::close(batch.ibo);
        Renderer::drawIndexed(batch.vao, icount);
        vcount = 0, icount = 0;
    }

    struct TriI {
        unsigned int a, b, c;
    };
    void Batch3d::submitTri(const Tri &tri) {
        if (vcount + 3 >= VCOUNT) {
            flush();
            begin();
        }

        *reinterpret_cast<Tri *>(vhandle) = tri;
        *reinterpret_cast<TriI *>(ihandle) = {0 + vcount, 1 + vcount, 2 + vcount};
        vhandle += 3, ihandle += 3;
        vcount += 3, icount += 3;
    }

    struct QuadI {
        unsigned int a1, a2, a3, b1, b2, b3;
    };
    void Batch3d::submitQuad(const Quad &quad) {
        if (vcount + 4 >= VCOUNT) {
            flush();
            begin();
        }

        *reinterpret_cast<Quad *>(vhandle) = quad;
        *reinterpret_cast<QuadI *>(ihandle) = {0 + vcount, 1 + vcount, 2 + vcount, 1 + vcount, 3 + vcount, 2 + vcount};
        vhandle += 4, ihandle += 6;
        vcount += 4, icount += 6;
    }
}} // namespace Coel::Renderer
