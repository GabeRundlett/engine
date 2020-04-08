#include "Batch2d.hpp"
#include <Coel/Renderer/Renderer.hpp>

#include <glad/glad.h>
#include <array>

static constexpr const char *const vertSrc = R"(
#version 440
layout (location = 0) in vec2 a_pos;
void main() {
	gl_Position = vec4(a_pos, 0, 1);
})";

static constexpr const char *const fragSrc = R"(
#version 440
out vec4 color;
void main() {
    color = vec4(1, 0, 0, 1);
})";

namespace Coel { namespace Renderer {
    constexpr unsigned int MAX_SPRITE_COUNT = 10000, MAX_VCOUNT = MAX_SPRITE_COUNT * 4, MAX_ICOUNT = MAX_SPRITE_COUNT * 6,
                           MAX_VSIZE = 10000 * 4 * sizeof(Batch2d::Vertex), MAX_ISIZE = 10000 * 6 * sizeof(unsigned int);
    Batch2d::Batch2d() : batch({{F32, 2}}, vertSrc, fragSrc) { init(batch, MAX_VSIZE, MAX_ISIZE); }
    Batch2d::~Batch2d() { deinit(batch); }
    void Batch2d::begin() {
        bind(batch.vao);
        open(batch.vbo, &vertexHandle);
        open(batch.ibo, &indexHandle);
    }

    void Batch2d::submitRect(float x, float y, float w, float h) {
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

    void Batch2d::flush() {
        Coel::close(batch.vbo);
        Coel::close(batch.ibo);
        batch.shader.bind();
        Coel::Renderer::drawIndexed(batch.vao, indexCount);
        vertexCount = 0, indexCount = 0;
    }
}} // namespace Coel::Renderer
