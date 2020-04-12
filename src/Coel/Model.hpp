#pragma once

#include <Coel/Renderer/Buffer.hpp>

namespace Coel {
    struct Model {
        struct Vertex {
            glm::vec3 pos, nrm;
            glm::vec2 tex;
            glm::vec4 col;
        };

        std::vector<Vertex> vertices{};
        Coel::Vao vao{};
        Coel::Vbo vbo{{{F32, 3}, {F32, 3}, {F32, 2}, {F32, 4}}};
    };

    void create(Model &model, const char *const filepath);
} // namespace Coel
