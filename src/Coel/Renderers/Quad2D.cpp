#include "Quad2d.hpp"

namespace Coel { namespace Renderer {
    static float quadVertices[]{-1, -1, 0, 0, -1, 1, 0, 1, 1, -1, 1, 0, 1, 1, 1, 1};
    static unsigned int quadIndices[]{0, 1, 2, 1, 3, 2};
    Quad2d::Quad2d()
        : m_vbo{quadVertices, sizeof(quadVertices), {{Element::F32, 2}, {Element::F32, 2}}}, m_ibo{quadIndices,
                                                                                                   sizeof(quadIndices)} {
        m_vao.add(m_vbo);
    }

    void Quad2d::draw() {
        m_ibo.bind();
        m_vao.drawIndexed(6);
    }
}} // namespace Coel::Renderer
