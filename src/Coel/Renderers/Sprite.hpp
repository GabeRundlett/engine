#pragma once

#include <Coel/Renderer/Batch.hpp>
#include <array>

namespace Coel {
    struct SpriteRenderer final {
        struct Vertex {
            glm::vec2 pos, tex;
            glm::vec4 color, info;
        };
        Renderer::Batch batch{{{F32, 4}, {F32, 4}, {F32, 4}}};
        Shader shader{};
        Vertex *vertexHandle{};
        unsigned int *indexHandle{};
        unsigned int vertexCount{}, indexCount{};
        glm::mat4 viewMat{1};
        Texture whiteTexture;
        Uniform<glm::mat4> u_view;
        std::array<const Texture *, 32> textures{};
        uint32_t textureCount{1};

        // Statistics
        uint32_t drawCallCount{}, submissionCount{};

        void begin();
        void submit(const std::array<Vertex, 4> &vertices);
        void submit(const glm::vec4 &pos_size, const glm::vec4 &tex_pos_size, const glm::vec4 &col, float tid = 0.f);
        void submit(const glm::vec4 &pos_size, const glm::vec4 &tex_pos_size, float r, const glm::vec4 &col, float tid = 0.f);
        void submit(const glm::vec4 &pos_size, const glm::vec4 &tex_pos_size, const Texture &texture,
                    const glm::vec4 &tint = {1, 1, 1, 1});
        void submit(const glm::vec4 &pos_size, const glm::vec4 &tex_pos_size, float r, const Texture &texture,
                    const glm::vec4 &tint = {1, 1, 1, 1});
        float getIndexOf(const Texture &texture);
        void flush();
        void resize(const float aspect, const float scale);
    };

    void init(SpriteRenderer &s);
    void deinit(SpriteRenderer &s);
} // namespace Coel
