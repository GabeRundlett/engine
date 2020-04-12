#include "Sprite.hpp"
#include <Coel/Renderer/Renderer.hpp>

#include <array>

static constexpr const char *const vertSrc = R"(
#version 450 core
layout (location = 0) in vec2 a_pos;
layout (location = 1) in vec2 a_tex;
uniform mat4 u_view;
out vec2 v_tex;
void main() {
    v_tex = a_tex;
    gl_Position = u_view * vec4(a_pos, 0, 1);
})";

static constexpr const char *const fragSrc = R"(
#version 450 core
in vec2 v_tex;
out vec4 frag_color;
uniform sampler2D u_tex;
void main() {
    // frag_color = texture(u_tex, v_tex);
    frag_color = vec4(1, 0, 1, 1);
})";

namespace Coel { namespace Renderer {
    constexpr unsigned int MAX_SPRITE_COUNT = 10000, MAX_VCOUNT = MAX_SPRITE_COUNT * 4, MAX_ICOUNT = MAX_SPRITE_COUNT * 6;
    constexpr unsigned int MAX_VSIZE = 10000 * 4 * sizeof(Sprite::Vertex), MAX_ISIZE = 10000 * 6 * sizeof(unsigned int);
    Sprite::Sprite() : batch{{{F32, 2}, {F32, 2}}} {
        init(batch, MAX_VSIZE, MAX_ISIZE);
        create(shader, vertSrc, fragSrc);
    }
    void Sprite::deinit() { Renderer::deinit(batch); }

    void Sprite::begin() {
        open(batch.vbo, &vertexHandle);
        open(batch.ibo, &indexHandle);
    }

    void Sprite::submit(float x, float y, float w, float h) {
        if (vertexCount + 4 > MAX_VCOUNT || indexCount + 6 > MAX_ICOUNT) {
            flush();
            begin();
        }

        *(std::array<Vertex, 4> *)vertexHandle = {{
            {x, y},
            {x, y + h},
            {x + w, y},
            {x + w, y + h},
        }};

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
    }

    void Sprite::flush() {
        close(batch.vbo);
        close(batch.ibo);
        bind(shader);
        Renderer::drawIndexed(batch.vao, indexCount);
        vertexCount = 0, indexCount = 0;
    }
}} // namespace Coel::Renderer
