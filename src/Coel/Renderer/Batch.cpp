#include "Batch.hpp"

namespace Coel { namespace Renderer {
    Batch::Batch(const Layout &l, const char *vertSrc, const char *fragSrc) : vbo{l}, shader(vertSrc, fragSrc) {}

    void init(Batch &b, const unsigned int vsize, const unsigned int isize) {
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
