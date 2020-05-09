#include "Sprite.hpp"
#include <Coel/Renderer/Renderer.hpp>
#include <glm/ext.hpp>

static constexpr const char *const vertSrc = R"(
#version 450 core
layout (location = 0) in vec4 a_postex;
layout (location = 1) in vec4 a_col;
layout (location = 2) in vec4 a_info;
uniform mat4 u_view;
out vec2 v_tex;
out vec4 v_col;
out vec4 v_info;
void main() {
    v_tex = a_postex.zw, v_col = a_col, v_info = a_info;
    gl_Position = u_view * vec4(a_postex.xy, 0, 1);
})";

static constexpr const char *const fragSrc = R"(
#version 450 core
in vec2 v_tex;
in vec4 v_col;
in vec4 v_info;
out vec4 frag_color;
uniform sampler2D u_tex[32];
void main() {
    const int tid = int(v_info.x);
    frag_color = texture(u_tex[tid], v_tex) * v_col;
})";

namespace Coel {
    constexpr unsigned int MAX_SPRITE_COUNT = 100000, MAX_VCOUNT = MAX_SPRITE_COUNT * 4, MAX_ICOUNT = MAX_SPRITE_COUNT * 6;
    constexpr unsigned int MAX_VSIZE = MAX_SPRITE_COUNT * 4 * sizeof(SpriteRenderer::Vertex),
                           MAX_ISIZE = MAX_SPRITE_COUNT * 6 * sizeof(unsigned int);

    void init(SpriteRenderer &s) {
        init(s.batch, MAX_VSIZE, MAX_ISIZE);
        create(s.shader, vertSrc, fragSrc);
        uint8_t whitePixel[]{255, 255, 255, 255};
        create(s.whiteTexture, {1, 1}, RGBA, whitePixel);
        s.u_view = findMat4(s.shader, "u_view");

        s.textures[0] = &s.whiteTexture;
        std::array<int32_t, 32> tids;
        for (uint32_t i = 0; i < 32; ++i)
            tids.at(i) = i;
        auto u_tex = findInt(s.shader, "u_tex");
        u_tex.count = 32;
        send(u_tex, tids.data());
    }
    void deinit(SpriteRenderer &s) {
        destroy(s.shader);
        Renderer::deinit(s.batch);
    }

    void SpriteRenderer::begin() {
        open(batch.vbo, &vertexHandle);
        open(batch.ibo, &indexHandle);
    }

    void SpriteRenderer::submit(const std::array<Vertex, 4> &vertices) {
        if (indexCount >= MAX_ICOUNT) {
            flush();
            begin();
        }
        *(std::array<Vertex, 4> *)vertexHandle = vertices;
        *(std::array<unsigned int, 6> *)indexHandle = {
            vertexCount + 0, //
            vertexCount + 1, //
            vertexCount + 2, //
            vertexCount + 1, //
            vertexCount + 3, //
            vertexCount + 2, //
        };
        vertexHandle += 4, indexHandle += 6;
        vertexCount += 4, indexCount += 6;

        ++submissionCount;
    }

    void SpriteRenderer::submit(const glm::vec4 &pos_size, const glm::vec4 &tex_pos_size, const glm::vec4 &col, float tid) {
        const glm::vec2 hs = {pos_size.z * 0.5f, pos_size.w * 0.5f};
        const glm::vec2 t1 = {tex_pos_size.x, tex_pos_size.y};
        const glm::vec2 t2 = {tex_pos_size.x + tex_pos_size.z, tex_pos_size.y + tex_pos_size.w};
        submit({{
            {{pos_size.x - hs.x, pos_size.y - hs.y}, {t1.x, t1.y}, col, {tid, 0, 0, 0}},
            {{pos_size.x - hs.x, pos_size.y + hs.y}, {t1.x, t2.y}, col, {tid, 0, 0, 0}},
            {{pos_size.x + hs.x, pos_size.y - hs.y}, {t2.x, t1.y}, col, {tid, 0, 0, 0}},
            {{pos_size.x + hs.x, pos_size.y + hs.y}, {t2.x, t2.y}, col, {tid, 0, 0, 0}},
        }});
    }
    void SpriteRenderer::submit(const glm::vec4 &pos_size, const glm::vec4 &tex_pos_size, float r, const glm::vec4 &col,
                                float tid) {
        const glm::vec2 hs = {pos_size.z * 0.5f, pos_size.w * 0.5f};
        const float s = std::sin(r), c = std::cos(r);
        const glm::vec2 rx = {hs.x * c, -hs.y * s};
        const glm::vec2 ry = {hs.x * s, hs.y * c};
        const glm::vec2 t1 = {tex_pos_size.x, tex_pos_size.y};
        const glm::vec2 t2 = {tex_pos_size.x + tex_pos_size.z, tex_pos_size.y + tex_pos_size.w};
        submit({{
            {{pos_size.x - rx.x - rx.y, pos_size.y - ry.x - ry.y}, {t1.x, t1.y}, col, {tid, 0, 0, 0}},
            {{pos_size.x - rx.x + rx.y, pos_size.y - ry.x + ry.y}, {t1.x, t2.y}, col, {tid, 0, 0, 0}},
            {{pos_size.x + rx.x - rx.y, pos_size.y + ry.x - ry.y}, {t2.x, t1.y}, col, {tid, 0, 0, 0}},
            {{pos_size.x + rx.x + rx.y, pos_size.y + ry.x + ry.y}, {t2.x, t2.y}, col, {tid, 0, 0, 0}},
        }});
    }
    void SpriteRenderer::submit(const glm::vec4 &pos_size, const glm::vec4 &tex_pos_size, const Texture &texture,
                                const glm::vec4 &tint) {
        float tid = getIndexOf(texture);
        submit(pos_size, tex_pos_size, tint, tid);
    }
    void SpriteRenderer::submit(const glm::vec4 &pos_size, const glm::vec4 &tex_pos_size, float r, const Texture &texture,
                                const glm::vec4 &tint) {
        float tid = getIndexOf(texture);
        submit(pos_size, tex_pos_size, r, tint, tid);
    }

    float SpriteRenderer::getIndexOf(const Texture &texture) {
        for (uint32_t i = 1; i < textureCount; ++i)
            if (textures[i] && textures[i]->id == texture.id)
                return i;

        textures[textureCount] = &texture;
        ++textureCount;
        return textureCount - 1;
    }

    void SpriteRenderer::flush() {
        close(batch.vbo);
        close(batch.ibo);
        bind(shader);
        send(u_view, &viewMat);
        for (uint32_t slot = 0; slot < textureCount; ++slot)
            bind(*textures[slot], slot);
        Renderer::drawIndexed(batch.vao, indexCount);
        vertexCount = 0, indexCount = 0;
        textureCount = 1;

        ++drawCallCount;
    }

    void SpriteRenderer::resize(const float aspect, const float scale) {
        viewMat = glm::ortho(-aspect, aspect, -scale, scale); //
    }
} // namespace Coel
