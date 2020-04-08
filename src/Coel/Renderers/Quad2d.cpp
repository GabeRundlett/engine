#include "Quad2d.hpp"
#include <Coel/Renderer/Renderer.hpp>

namespace Coel { namespace Renderer {
    static float quadVertices[]{-1, -1, 0, 0, -1, 1, 0, 1, 1, -1, 1, 0, 1, 1, 1, 1};
    static unsigned int quadIndices[]{0, 1, 2, 1, 3, 2};
    Quad2d::Quad2d() {
        create(m_vao);
        create(m_vbo, quadVertices, sizeof(quadVertices));
        create(m_ibo, quadIndices, sizeof(quadIndices));
        link(m_vao, m_vbo);
    }

    void Quad2d::draw() {
        bind(m_ibo);
        Renderer::drawIndexed(m_vao, 6);
    }
}} // namespace Coel::Renderer
