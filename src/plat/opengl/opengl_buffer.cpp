#include "common.hpp"
#include <coel/renderer/buffer.hpp>

#include <debug/debug.hpp>

namespace coel { namespace opengl {
    Vbo::Vbo(const void *const data, const size_t size, const Layout &layout) : m_size(size), coel::Vbo(layout) {
        DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(glGenBuffers(1, &m_id));
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_id));
        if (data) {
            m_count = size / m_layout.stride;
            COEL_DEBUG_ONLY(m_buffertype = BufferType::Static);
            GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
            m_buffer_start = nullptr, m_buffer_pointer = nullptr;
            COEL_DEBUG_ONLY(m_locked = true);
        } else {
            m_count = 0;
            COEL_DEBUG_ONLY(m_buffertype = BufferType::Dynamic);
            GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
            GL_CALL(m_buffer_start = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
            m_buffer_pointer = m_buffer_start;
            COEL_DEBUG_ONLY(m_locked = false);
        }
    }

    void Vbo::bind() const {
        DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_id));
    }

    void Vbo::lock() {
        DEBUG_BEGIN_FUNC_PROFILE;

        COEL_ASSERT(!m_locked);
        COEL_ASSERT(m_buffertype == BufferType::Dynamic);
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_id));
        GL_CALL(glUnmapBuffer(GL_ARRAY_BUFFER));
        COEL_DEBUG_ONLY(m_locked = true);
    }

    void Vbo::unlock() {
        DEBUG_BEGIN_FUNC_PROFILE;

        COEL_ASSERT(m_locked);
        COEL_ASSERT(m_buffertype == BufferType::Dynamic);
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_id));
        GL_CALL(m_buffer_start = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
        m_buffer_pointer = m_buffer_start;
        COEL_DEBUG_ONLY(m_locked = false);
    }

    size_t Vbo::get_count() const {
        DEBUG_BEGIN_FUNC_PROFILE;

        return m_count;
    }

    Ibo::Ibo(const unsigned short *const data, const size_t size) : m_size(size) {
        DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(glGenBuffers(1, &m_id));
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
        if (data) {
            m_count = size / sizeof(unsigned short);
            COEL_DEBUG_ONLY(m_buffertype = BufferType::Static);
            GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
            m_buffer_start = nullptr, m_buffer_pointer = nullptr;
            COEL_DEBUG_ONLY(m_locked = true);
        } else {
            m_count = 0;
            COEL_DEBUG_ONLY(m_buffertype = BufferType::Dynamic);
            GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
            GL_CALL(m_buffer_start = reinterpret_cast<unsigned short *>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY)));
            m_buffer_pointer = m_buffer_start;
            COEL_DEBUG_ONLY(m_locked = false);
        }
    }

    void Ibo::bind() const {
        DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
    }

    void Ibo::lock() {
        DEBUG_BEGIN_FUNC_PROFILE;

        COEL_ASSERT(!m_locked);
        COEL_ASSERT(m_buffertype == BufferType::Dynamic);
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
        GL_CALL(glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER));
        COEL_DEBUG_ONLY(m_locked = true);
    }

    void Ibo::unlock() {
        DEBUG_BEGIN_FUNC_PROFILE;

        COEL_ASSERT(m_locked);
        COEL_ASSERT(m_buffertype == BufferType::Dynamic);
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
        GL_CALL(m_buffer_start = reinterpret_cast<unsigned short *>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY)));
        m_buffer_pointer = m_buffer_start;
        COEL_DEBUG_ONLY(m_locked = false);
    }

    size_t Ibo::get_count() const {
        DEBUG_BEGIN_FUNC_PROFILE;

        return m_count;
    }

    static inline constexpr GLenum to_gltype(const Type type) {
        switch (type) {
        case Type::f32: return GL_FLOAT;
        case Type::u8: return GL_UNSIGNED_BYTE;
        default: return 0;
        }
    }

    Vao::Vao() {
        DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(glGenVertexArrays(1, &m_id));
        GL_CALL(glBindVertexArray(m_id));
    }

    void Vao::bind() const {
        DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(glBindVertexArray(m_id));
    }

    void Vao::draw(const Ref<coel::Ibo> ibo) const {
        DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(glBindVertexArray(m_id));
        ibo->bind();
        GL_CALL(glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(ibo->get_count()), GL_UNSIGNED_SHORT, nullptr));
    }

    void Vao::add_vbo(const Ref<coel::Vbo> vbo) {
        DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(glBindVertexArray(m_id));
        vbo->bind();
        unsigned char *offset = nullptr;
        for (const auto elem : vbo->m_layout.elements) {
            GL_CALL(glEnableVertexAttribArray(m_attrib_count));
            GL_CALL(glVertexAttribPointer(m_attrib_count, static_cast<GLint>(elem.count), to_gltype(elem.type), GL_FALSE,
                                          static_cast<GLsizei>(vbo->m_layout.stride), offset));
            offset += elem.size;
            ++m_attrib_count;
        }
    }
}} // namespace coel::opengl
