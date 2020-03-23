#pragma once

#include <Coel/Renderer/Buffer.hpp>
#include <Coel/Renderer/Shader.hpp>
#include <Coel/Renderer/Texture.hpp>

#include <glm/glm.hpp>

namespace Coel { namespace Renderer {
    class Batch2d final {
        Vao m_vao;
        Vbo m_vbo;
        Ibo m_ibo;
        Shader m_shader;
        Shader::Uniform<glm::vec2> m_viewPosUniform, m_viewSizeUniform;

        struct Vertex {
            glm::vec2 pos, tex, size;
            glm::u8vec4 fill, param;
        };

        typedef unsigned int Index;

        Vertex *m_vertices{};
        Index *m_indices{};

        struct Quad {
            const glm::vec2 p1, p2, t1, t2;
            const glm::u8vec4 param;
        };

        unsigned int m_vertexCount{}, m_indexCount{}, m_maxVertexCount, m_maxIndexCount;
        float m_strokeWeight;
        glm::u8vec4 m_fillCol{255, 0, 255, 255};

        inline void submitQuad(const Quad &q) {
            if (m_vertexCount + 4 > m_maxVertexCount || m_indexCount + 6 > m_maxIndexCount) {
                flush();
                begin();
            }

            glm::vec2 p1 = q.p1, p2 = q.p2, t1 = q.t1, t2 = q.t1;

            if (q.p1.x > p2.x)
                p1.x = q.p2.x, p2.x = q.p1.x, t1.x = q.t2.x, t2.x = q.t1.x;
            else
                p1.x = q.p1.x, p2.x = q.p2.x, t1.x = q.t1.x, t2.x = q.t2.x;
            if (q.p1.y > p2.y)
                p1.y = q.p2.y, p2.y = q.p1.y, t1.y = q.t2.y, t2.y = q.t1.y;
            else
                p1.y = q.p1.y, p2.y = q.p2.y, t1.y = q.t1.y, t2.y = q.t2.y;

            p1 -= glm::vec2{(float)q.param.g, (float)q.param.g};
            p2 += glm::vec2{(float)q.param.g, (float)q.param.g};

            const glm::vec2 size = p2 - p1;

            struct QuadVBO {
                Vertex a, b, c, d;
            };
            *reinterpret_cast<QuadVBO *>(m_vertices) = {
                {p1, t1, size, m_fillCol, q.param},
                {{p1.x, p2.y}, {t1.x, t2.y}, size, m_fillCol, q.param},
                {{p2.x, p1.y}, {t2.x, t1.y}, size, m_fillCol, q.param},
                {p2, t2, size, m_fillCol, q.param},
            };

            struct QuadIBO {
                Index a1, a2, a3, b1, b2, b3;
            };
            *reinterpret_cast<QuadIBO *>(m_indices) = {
                Index(m_vertexCount + 0), Index(m_vertexCount + 1), Index(m_vertexCount + 2),
                Index(m_vertexCount + 1), Index(m_vertexCount + 3), Index(m_vertexCount + 2),
            };

            m_vertices += 4, m_indices += 6;
            m_vertexCount += 4, m_indexCount += 6;
        }

      public:
        Batch2d(const char *const vsrc, const char *const fsrc, unsigned int vCount = 10000, unsigned int iCount = 10000);
        Batch2d(unsigned int vCount = 10000, unsigned int iCount = 10000);
        ~Batch2d() = default;

        void begin();
        void flush();

        void submitRect(float x, float y, float w, float h);
        void submitLine(float x1, float y1, float x2, float y2);
        void submitEllipse(float x, float y, float rx, float ry);
        void fill(const glm::u8vec4 &c);
        void strokeWeight(const float weight);

        void resize(const glm::vec2 &pos, const glm::vec2 &size);
    };
}} // namespace Coel::Renderer
