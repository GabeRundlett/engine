#pragma once

#include <Coel/Renderer/Buffer.hpp>
#include <Coel/Renderer/Shader.hpp>
#include <Coel/Renderer/Texture.hpp>

#include <Math.hpp>
#include <string>

namespace Coel { namespace Renderer {
    class BatchText final {
        Vao m_vao;
        Vbo m_vbo;
        Ibo m_ibo;
        Shader m_shader;
        Texture m_texture;

        struct Vertex {
            Math::Vec2 pos, tex, size;
            Math::Color fill, param;
        };

        typedef unsigned short Index;

        Vertex *m_vertices;
        Index *m_indices;

        struct Quad {
            const Math::Vec2 p1, p2, t1, t2;
            const Math::Color param;
        };

        unsigned int m_vertexCount, m_indexCount, m_maxVertexCount, m_maxIndexCount;
        Math::Color m_fillCol;

        inline void submitQuad(const Quad &q) {
            if (m_vertexCount + 4 > m_maxVertexCount || m_indexCount + 6 > m_maxIndexCount) flush();

            Math::Vec2 p1 = q.p1, p2 = q.p2, t1 = q.t1, t2 = q.t1;

            if (q.p1.x > p2.x)
                p1.x = q.p2.x, p2.x = q.p1.x, t1.x = q.t2.x, t2.x = q.t1.x;
            else
                p1.x = q.p1.x, p2.x = q.p2.x, t1.x = q.t1.x, t2.x = q.t2.x;
            if (q.p1.y > p2.y)
                p1.y = q.p2.y, p2.y = q.p1.y, t1.y = q.t2.y, t2.y = q.t1.y;
            else
                p1.y = q.p1.y, p2.y = q.p2.y, t1.y = q.t1.y, t2.y = q.t2.y;

            p1 -= {(float)q.param.g, (float)q.param.g};
            p2 += {(float)q.param.g, (float)q.param.g};

            const Math::Vec2 size = p2 - p1;

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
        BatchText(unsigned int vCount = 10000, unsigned int iCount = 10000);
        ~BatchText() = default;

        void init();
        void flush();

        void submitText(float x, float y, float s, const std::string &str);
        void fill(const Math::Color &c);

        void resize(const Math::Vec2i &size);
    };
}} // namespace Coel::Renderer
