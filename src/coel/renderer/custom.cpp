#include "../../coel.hpp"
#include <glad/glad.h>

namespace coel { namespace renderer { namespace custom {
    static constexpr unsigned int s_vbuffer_size = 4096, s_ibuffer_size = 4096;
    static unsigned int s_vao_id, s_vbo_id, s_ibo_id;
    static unsigned char *s_vbuffer_pointer;
    static unsigned short *s_ibuffer_pointer;
    static unsigned int s_vertex_count = 0, s_index_count = 0;
    static unsigned short s_layout_count = 0, s_layout_stride = 0;
    static unsigned char *s_layout_begin = 0;
    void init() {
        glGenVertexArrays(1, &s_vao_id);
        glBindVertexArray(s_vao_id);

        glGenBuffers(1, &s_vbo_id);
        glBindBuffer(GL_ARRAY_BUFFER, s_vbo_id);
        glBufferData(GL_ARRAY_BUFFER, s_vbuffer_size, nullptr, GL_DYNAMIC_DRAW);

        glGenBuffers(1, &s_ibo_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_ibo_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, s_ibuffer_size, nullptr, GL_DYNAMIC_DRAW);

        s_vbuffer_pointer = reinterpret_cast<unsigned char *>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
        s_ibuffer_pointer = reinterpret_cast<unsigned short *>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));
    }
    void submit(const Model *const model) {
        const unsigned int vsize = model->vsize, isize = model->isize;
        const unsigned char *vdata = reinterpret_cast<const unsigned char *>(model->vdata);
        const unsigned short *idata = model->idata;
        for (unsigned int i = 0; i < vsize; ++i)
            s_vbuffer_pointer[i] = vdata[i];
        s_vbuffer_pointer += vsize;
        const unsigned short index_count = isize / sizeof(unsigned short);
        for (unsigned int i = 0; i < index_count; ++i)
            s_ibuffer_pointer[i] = idata[i] + s_vertex_count;
        s_vertex_count += vsize / s_layout_stride;
        s_ibuffer_pointer += index_count;
        s_index_count += index_count;
    }
    void flush() {
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
        glBindVertexArray(s_vao_id);
        glDrawElements(GL_TRIANGLES, s_index_count, GL_UNSIGNED_SHORT, nullptr);
        s_vbuffer_pointer = reinterpret_cast<unsigned char *>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
        s_ibuffer_pointer = reinterpret_cast<unsigned short *>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));
        s_vertex_count = 0;
        s_index_count = 0;
    }
    void setup_layout(const LayoutType type, const unsigned int count) {
        ++s_layout_count;
        switch (type) {
        case LayoutType::Float: s_layout_stride += 4 * count; break;
        case LayoutType::Int: s_layout_stride += 4 * count; break;
        case LayoutType::UInt: s_layout_stride += 4 * count; break;
        case LayoutType::Short: s_layout_stride += 2 * count; break;
        case LayoutType::UShort: s_layout_stride += 2 * count; break;
        case LayoutType::Byte: s_layout_stride += count; break;
        case LayoutType::UByte: s_layout_stride += count; break;
        default: break; // Invalid layout type
        }
    }
    void set_layout(const unsigned int i, const LayoutType type, const unsigned int count) {
        glEnableVertexAttribArray(i);
        unsigned int gl_type;
        switch (type) {
        case LayoutType::Float:
            glVertexAttribPointer(i, count, GL_FLOAT, GL_FALSE, s_layout_stride, s_layout_begin);
            s_layout_begin += 4 * count;
            break;
        case LayoutType::Int:
            glVertexAttribPointer(i, count, GL_INT, GL_FALSE, s_layout_stride, s_layout_begin);
            s_layout_begin += 4 * count;
            break;
        case LayoutType::UInt:
            glVertexAttribPointer(i, count, GL_UNSIGNED_INT, GL_FALSE, s_layout_stride, reinterpret_cast<const void *>(0));
            s_layout_begin += 4 * count;
            break;
        case LayoutType::Short:
            glVertexAttribPointer(i, count, GL_SHORT, GL_FALSE, s_layout_stride, s_layout_begin);
            s_layout_begin += 2 * count;
            break;
        case LayoutType::UShort:
            glVertexAttribPointer(i, count, GL_UNSIGNED_SHORT, GL_FALSE, s_layout_stride, s_layout_begin);
            s_layout_begin += 2 * count;
            break;
        case LayoutType::Byte:
            glVertexAttribPointer(i, count, GL_BYTE, GL_FALSE, s_layout_stride, s_layout_begin);
            s_layout_begin += count;
            break;
        case LayoutType::UByte:
            glVertexAttribPointer(i, count, GL_UNSIGNED_BYTE, GL_FALSE, s_layout_stride, s_layout_begin);
            s_layout_begin += count;
            break;
        default: break; // Invalid layout type
        }
    }
}}} // namespace coel::renderer::custom
