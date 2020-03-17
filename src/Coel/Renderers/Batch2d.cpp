#include "Batch2d.hpp"
#include <glad/glad.h>

#include "Assets/Batch2dShader.hpp"

namespace Coel { namespace Renderer {
    Batch2d::Batch2d(const char *const vsrc, const char *const fsrc, unsigned int vCount, unsigned int iCount)
        : m_vao(), m_vbo(nullptr, sizeof(Vertex) * vCount,
                         {{Element::F32, 2}, {Element::F32, 2}, {Element::F32, 2}, {Element::U8, 4}, {Element::U8, 4}}),
          m_ibo(nullptr, sizeof(Index) * iCount),
          m_shader(vsrc, fsrc), m_viewPosUniform{m_shader.findInt2("viewportPos")}, m_viewSizeUniform{m_shader.findInt2(
                                                                                        "viewportSize")},
          m_maxVertexCount(vCount), m_maxIndexCount(iCount), m_strokeWeight(4), m_fillCol{0} {
        m_vao.add(m_vbo);
    }

    Batch2d::Batch2d(unsigned int vCount, unsigned int iCount) : Batch2d::Batch2d(vertSrc, fragSrc, vCount, iCount) {}

    void Batch2d::begin() {
        m_vao.bind();
        m_vbo.open(&m_vertices);
        m_ibo.open(&m_indices);
    }

    void Batch2d::submitRect(float x, float y, float w, float h) {
        submitQuad({{x, y}, {x + w, y + h}, {0, 0}, {1, 1}, {0, 0, 0, 0}}); //
    }

    void Batch2d::submitLine(float x1, float y1, float x2, float y2) {
        submitQuad({{x1, y1}, {x2, y2}, {0.f, 0.f}, {1.f, 1.f}, glm::u8vec4(1.f, (float)m_strokeWeight, 0.f, 0.f)}); //
    }

    void Batch2d::submitEllipse(float x, float y, float rx, float ry) {
        submitQuad({{x - rx, y - ry}, {x + rx, y + ry}, {0, 0}, {1, 1}, {2, 0, 0, 0}}); //
    }

    void Batch2d::flush() {
        m_vbo.close();
        m_ibo.close();

        m_shader.bind();
        m_vao.drawIndexed(m_indexCount);

        m_vertexCount = 0, m_indexCount = 0;
    }

    void Batch2d::fill(const glm::u8vec4 &c) { m_fillCol = c; }
    void Batch2d::strokeWeight(const float weight) { m_strokeWeight = weight; }

    void Batch2d::resize(const glm::ivec2 &pos, const glm::ivec2 &size) {
        m_shader.send(m_viewPosUniform, &pos);
        m_shader.send(m_viewSizeUniform, &size);
    }
}} // namespace Coel::Renderer
