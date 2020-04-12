#include "Batch.hpp"

namespace Coel { namespace Renderer {
    Batch::Batch(const Layout &l) : vbo{l} {}

    void init(Batch &b, const uint32_t vsize, const uint32_t isize) {
        create(b.vao);
        create(b.vbo, nullptr, vsize);
        create(b.ibo, nullptr, isize);
        link(b.vao, b.vbo);
    }
    void deinit(Batch &b) {
        destroy(b.vao);
        destroy(b.vbo);
        destroy(b.ibo);
    }
}} // namespace Coel::Renderer
