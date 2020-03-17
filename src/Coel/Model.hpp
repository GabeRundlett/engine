#pragma once

#include <Coel/Renderer/Buffer.hpp>
#include <glm/glm.hpp>

namespace Coel {
    class Model final {
        struct Vertex {
            glm::vec3 pos, nrm;
            glm::vec2 tex;
            glm::vec4 col;
        };

        std::vector<Vertex> m_vertices;
        Coel::Vao m_vao;
        Coel::Vbo m_vbo;

        static std::vector<Vertex> loadModel(const char *const filepath);

      public:
        Model(const char *const filepath);
        void draw();
    };
} // namespace Coel
