#include "../../coel.hpp"
#include <glad/glad.h>

namespace coel { namespace renderer { namespace batch2d {
    static constexpr unsigned int s_sprite_count = 10000, s_vbuffer_size = 4 * sizeof(Vertex) * s_sprite_count,
                                  s_ibuffer_size = 6 * s_sprite_count;
    static unsigned int s_vao_id, s_vbo_id, s_ibo_id;
    static unsigned short s_indices[s_ibuffer_size];
    static unsigned int s_index_count = 0;
    static Vertex *s_vbuffer_pointer;

    static unsigned int s_viewport_width, s_viewport_height;

    void init(const unsigned int width, const unsigned int height) {
        resize(width, height);

        glGenVertexArrays(1, &s_vao_id);
        glBindVertexArray(s_vao_id);

        glGenBuffers(1, &s_vbo_id);
        glBindBuffer(GL_ARRAY_BUFFER, s_vbo_id);
        glBufferData(GL_ARRAY_BUFFER, s_vbuffer_size, nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)8);
        glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), (const void *)16);
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)20);

        for (unsigned int i = 0; i < s_sprite_count; ++i) {
            const unsigned int index = i * 6, offset = i * 4;
            s_indices[index] = offset;
            s_indices[index + 1] = 1 + offset;
            s_indices[index + 2] = 2 + offset;
            s_indices[index + 3] = 1 + offset;
            s_indices[index + 4] = 3 + offset;
            s_indices[index + 5] = 2 + offset;
        }

        glGenBuffers(1, &s_ibo_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_ibo_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(s_indices), s_indices, GL_STATIC_DRAW);

        s_vbuffer_pointer = reinterpret_cast<Vertex *>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
    }

    void resize(const unsigned int width, const unsigned int height) { s_viewport_width = width, s_viewport_height = height; }

    void fill_rect(const float pos_x, const float pos_y, const float size_x, const float size_y) {
        const float px = 2.f * pos_x / s_viewport_width - 1, py = -2.f * pos_y / s_viewport_height + 1,
                    sx = 2.f * size_x / s_viewport_width, sy = -2.f * size_y / s_viewport_height;

        s_vbuffer_pointer->pos_x = px;
        s_vbuffer_pointer->pos_y = py;
        s_vbuffer_pointer->tex_u = 0.f;
        s_vbuffer_pointer->tex_v = 0.f;
        s_vbuffer_pointer->tid = -1.f;
        s_vbuffer_pointer->col_r = 156;
        s_vbuffer_pointer->col_g = 102;
        s_vbuffer_pointer->col_b = 255;
        s_vbuffer_pointer->col_a = 255;
        ++s_vbuffer_pointer;
        s_vbuffer_pointer->pos_x = px;
        s_vbuffer_pointer->pos_y = py + sy;
        s_vbuffer_pointer->tex_u = 0.f;
        s_vbuffer_pointer->tex_v = 1.f;
        s_vbuffer_pointer->tid = -1.f;
        s_vbuffer_pointer->col_r = 156;
        s_vbuffer_pointer->col_g = 102;
        s_vbuffer_pointer->col_b = 255;
        s_vbuffer_pointer->col_a = 255;
        ++s_vbuffer_pointer;
        s_vbuffer_pointer->pos_x = px + sx;
        s_vbuffer_pointer->pos_y = py;
        s_vbuffer_pointer->tex_u = 1.f;
        s_vbuffer_pointer->tex_v = 0.f;
        s_vbuffer_pointer->tid = -1.f;
        s_vbuffer_pointer->col_r = 156;
        s_vbuffer_pointer->col_g = 102;
        s_vbuffer_pointer->col_b = 255;
        s_vbuffer_pointer->col_a = 255;
        ++s_vbuffer_pointer;
        s_vbuffer_pointer->pos_x = px + sx;
        s_vbuffer_pointer->pos_y = py + sy;
        s_vbuffer_pointer->tex_u = 1.f;
        s_vbuffer_pointer->tex_v = 1.f;
        s_vbuffer_pointer->tid = -1.f;
        s_vbuffer_pointer->col_r = 156;
        s_vbuffer_pointer->col_g = 102;
        s_vbuffer_pointer->col_b = 255;
        s_vbuffer_pointer->col_a = 255;
        ++s_vbuffer_pointer;
        s_index_count += 6;
    }

    void flush() {
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glBindVertexArray(s_vao_id);
        glDrawElements(GL_TRIANGLES, s_index_count, GL_UNSIGNED_SHORT, nullptr);
        s_vbuffer_pointer = reinterpret_cast<Vertex *>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
        s_index_count = 0;
    }
}}} // namespace coel::renderer::batch2d
