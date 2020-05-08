#pragma once

#include <Coel/Renderer/Buffer.hpp>
#include <string>

namespace Coel {
    struct Model {
        struct Vertex {
            glm::vec3 pos, nrm;
            glm::vec2 tex;
        };

        struct Object {
            Vao vao;
            Vbo vbo{{{F32, 3}, {F32, 3}, {F32, 2}}};
            Ibo ibo;
            std::vector<Texture> textures;
            uint32_t indexCount;
        };

        std::vector<Object> objects;
    };

    void open(Model &model, std::string filepath);
} // namespace Coel
