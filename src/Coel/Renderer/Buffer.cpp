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

    Fbo::Fbo(unsigned int width, unsigned int height, unsigned char flags) : m_width(width), m_height(height), m_flags(flags) {
        // Create the buffer
        glGenFramebuffers(1, &m_id);
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);

        // Create a color texture attachment
        if (flags & Buffer::Color) {
            GLenum drawBuffers[]{GL_COLOR_ATTACHMENT0};
            glDrawBuffers(1, drawBuffers);

            glGenTextures(1, &m_colTexId);
            glBindTexture(GL_TEXTURE_2D, m_colTexId);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
            glTextureParameteri(m_colTexId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTextureParameteri(m_colTexId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTextureParameteri(m_colTexId, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTextureParameteri(m_colTexId, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colTexId, 0);
        }
        
        // Create a depth texture attachment
        if (flags & Buffer::Depth) {
            glGenTextures(1, &m_depTexId);
            glBindTexture(GL_TEXTURE_2D, m_depTexId);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
            glTextureParameteri(m_depTexId, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTextureParameteri(m_depTexId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTextureParameteri(m_depTexId, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTextureParameteri(m_depTexId, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depTexId, 0);
        }

        // Create a depth render buffer
        if (flags & Buffer::RenderDepth) {
            glGenRenderbuffers(1, &m_depRboId);
            glBindRenderbuffer(GL_RENDERBUFFER, m_depRboId);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depRboId);
            // std::cout << "Created depth render buffer\n";
        }
    }

    Fbo::~Fbo() {
        if (m_flags & Buffer::RenderDepth) glDeleteRenderbuffers(1, &m_depRboId);
        if (m_flags & Buffer::Depth) glDeleteTextures(1, &m_depTexId);
        if (m_flags & Buffer::Color) glDeleteTextures(1, &m_colTexId);
        glDeleteFramebuffers(1, &m_id);
    }

    void Fbo::bind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);
        glViewport(0, 0, m_width, m_height);
    }

    void Fbo::unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0); }

    void Fbo::bindColorTexture(int slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_colTexId);
        // glBindTextureUnit(slot, m_colTexId);
    }

    void Fbo::bindDepthTexture(int slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_depTexId);
        // glBindTextureUnit(slot, m_colTexId);
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
