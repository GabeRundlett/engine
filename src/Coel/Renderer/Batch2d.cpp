#include "Renderer.hpp"
#include <glad/glad.h>

namespace Coel { namespace Renderer {
    Batch2d::Batch2d(unsigned int vCount, unsigned int iCount)
        : m_vao(), m_vbo(nullptr, sizeof(Vertex) * vCount,
                         {{Element::F32, 2}, {Element::F32, 2}, {Element::F32, 2}, {Element::U8, 4}, {Element::U8, 4}}),
          m_ibo(nullptr, sizeof(Index) * iCount), m_vertices(nullptr), m_indices(nullptr), m_vertexCount(0), m_indexCount(0),
          m_maxVertexCount(vCount), m_maxIndexCount(iCount), m_fillCol{0} {
        m_vao.add(m_vbo);
        init();
    }

    void Batch2d::init() {
        m_vbo.open(&m_vertices);
        m_ibo.open(&m_indices);
    }

    void Batch2d::submitRect(float x, float y, float w, float h) {
        submitQuad({{x, y}, {x + w, y + h}, {0, 0}, {1, 1}, {0, 0, 0, 0}}); //
    }

    void Batch2d::submitLine(float x1, float y1, float x2, float y2) {
        submitQuad({{x1, y1}, {x2, y2}, {0, 0}, {1, 1}, {1, 5, 0, 0}}); //
    }

    void Batch2d::submitEllipse(float x, float y, float rx, float ry) {
        submitQuad({{x - rx, y - ry}, {x + rx, y + ry}, {0, 0}, {1, 1}, {2, 0, 0, 0}}); //
    }

    void Batch2d::flush() {
        m_vbo.close();
        m_ibo.close();

        m_vao.drawIndexed(m_indexCount);

        m_vbo.open(&m_vertices);
        m_ibo.open(&m_indices);

        m_vertexCount = 0, m_indexCount = 0;
    }

    void Batch2d::fill(const Math::Color &c) { m_fillCol = c; }
}} // namespace Coel::Renderer
