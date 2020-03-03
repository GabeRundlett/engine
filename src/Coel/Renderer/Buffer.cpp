#include "Buffer.hpp"

#include <glad/glad.h>

namespace Coel {
    static inline constexpr GLenum toOpenGLType(Element::Type t) {
        switch (t) {
        case Element::I8: return GL_BYTE;
        case Element::U8: return GL_UNSIGNED_BYTE;
        case Element::F16: return GL_HALF_FLOAT;
        case Element::I16: return GL_SHORT;
        case Element::U16: return GL_UNSIGNED_SHORT;
        case Element::F32: return GL_FLOAT;
        case Element::I32: return GL_INT;
        case Element::U32: return GL_UNSIGNED_INT;
        case Element::F64: return GL_DOUBLE;
        default: return NULL;
        }
    }

    Vbo::Vbo(void *data, unsigned int size, const Layout &l) : m_layout(l) {
        glCreateBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);

        if (data) {
            glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        } else {
            glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
        }
    }

    Vbo::~Vbo() {
        glDeleteBuffers(1, &m_id); //
    }

    void Vbo::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_id); //
    }

    void Vbo::setLayout(const Layout &l) {
        m_layout = l; //
    }

    void Vbo::open(void *handle) const {
        bind();
        *reinterpret_cast<void **>(handle) = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    }

    void Vbo::close() const {
        bind();
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }

    Ibo::Ibo(unsigned int *data, unsigned int size) {
        glCreateBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);

        if (data) {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        } else {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
        }
    }

    Ibo::~Ibo() {
        glDeleteBuffers(1, &m_id); //
    }

    void Ibo::bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id); //
    }

    void Ibo::open(void *handle) const {
        bind();
        *reinterpret_cast<void **>(handle) = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
    }

    void Ibo::close() const {
        bind();
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    }

    Vao::Vao() : m_attribCount(0) {
        glGenVertexArrays(1, &m_id);
        glBindVertexArray(m_id);
    }

    Vao::~Vao() {
        glDeleteVertexArrays(1, &m_id); //
    }

    void Vao::bind() const {
        glBindVertexArray(m_id); //
    }

    void Vao::add(const Vbo &v) {
        glBindVertexArray(m_id);
        v.bind();
        unsigned char *offset = nullptr;
        for (const auto elem : v.m_layout.elements) {
            glEnableVertexAttribArray(m_attribCount);
            glVertexAttribPointer(m_attribCount, static_cast<GLint>(elem.count), toOpenGLType(elem.type), GL_FALSE,
                                  static_cast<GLsizei>(v.m_layout.stride), offset);
            offset += elem.getSize();
            ++m_attribCount;
        }
    }

    void Vao::draw(unsigned int count) const {
        bind();
        glDrawArrays(GL_TRIANGLES, 0, count);
    }

    void Vao::drawIndexed(unsigned int count) const {
        bind();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }
} // namespace Coel
