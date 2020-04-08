#include "Buffer.hpp"

#include <glad/glad.h>

namespace Coel {
    static inline constexpr GLenum toOpenGLType(unsigned int t) {
        switch (t) {
        case I8: return GL_BYTE;
        case U8: return GL_UNSIGNED_BYTE;
        case F16: return GL_HALF_FLOAT;
        case I16: return GL_SHORT;
        case U16: return GL_UNSIGNED_SHORT;
        case F32: return GL_FLOAT;
        case I32: return GL_INT;
        case U32: return GL_UNSIGNED_INT;
        case F64: return GL_DOUBLE;
        default: return GL_FLOAT;
        }
    }

    static inline void toOpenGLColorFormat(unsigned char attachment, GLenum data[3]) {
        switch (attachment) {
        case ColorBuffer::RGB8: data[0] = GL_RGB, data[1] = GL_RGB, data[2] = GL_UNSIGNED_BYTE; return;
        case ColorBuffer::RGB16: data[0] = GL_RGB16F, data[1] = GL_RGB, data[2] = GL_FLOAT; return;
        case ColorBuffer::RGBA8: data[0] = GL_RGBA, data[1] = GL_RGBA, data[2] = GL_UNSIGNED_BYTE; return;
        case ColorBuffer::RGBA16: data[0] = GL_RGBA16F, data[1] = GL_RGBA, data[2] = GL_FLOAT; return;
        case ColorBuffer::Float: data[0] = GL_RED, data[1] = GL_RGB, data[2] = GL_FLOAT; return;
        }
    }

    Fbo::Fbo(unsigned int width, unsigned int height, const std::initializer_list<unsigned char> &colorAttachments,
             const unsigned char depthAttachment)
        : m_width(width), m_height(height), m_colorAttachmentCount(colorAttachments.size()),
          m_depthAttachment(depthAttachment) {
        // Create the buffer
        glGenFramebuffers(1, &m_id);
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);

        if (m_colorAttachmentCount > 4) {
            m_colorAttachmentCount = 0;
            return;
        }

        // Create a color texture attachment
        if (m_colorAttachmentCount > 0) {
            GLenum drawBuffers[4]{GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
            glDrawBuffers(m_colorAttachmentCount, drawBuffers);

            for (unsigned int i = 0; i < m_colorAttachmentCount; ++i) {
                glGenTextures(1, m_colTexId + i);
                glBindTexture(GL_TEXTURE_2D, m_colTexId[i]);

                GLenum formatData[3]{0, 0, 0};
                m_colorAttachments[i] = colorAttachments.begin()[i];
                toOpenGLColorFormat(m_colorAttachments[i], formatData);

                glTexImage2D(GL_TEXTURE_2D, 0, formatData[0], width, height, 0, formatData[1], formatData[2], nullptr);
                glTextureParameteri(m_colTexId[i], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTextureParameteri(m_colTexId[i], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTextureParameteri(m_colTexId[i], GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTextureParameteri(m_colTexId[i], GL_TEXTURE_WRAP_T, GL_REPEAT);
                glFramebufferTexture2D(GL_FRAMEBUFFER, drawBuffers[i], GL_TEXTURE_2D, m_colTexId[i], 0);
            }
        }

        if (m_depthAttachment == DepthBuffer::RenderBuffer) {
            // Create a depth render buffer
            glGenRenderbuffers(1, &m_depRboId);
            glBindRenderbuffer(GL_RENDERBUFFER, m_depRboId);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depRboId);
        } else if (m_depthAttachment > DepthBuffer::None) {
            // Create a depth texture attachment
            glGenTextures(1, &m_depTexId);
            glBindTexture(GL_TEXTURE_2D, m_depTexId);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
            glTextureParameteri(m_depTexId, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTextureParameteri(m_depTexId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTextureParameteri(m_depTexId, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTextureParameteri(m_depTexId, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            float borderColor[]{1, 1, 1, 1};
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depTexId, 0);
        }
    }

    Fbo::~Fbo() {
        if (m_depthAttachment == DepthBuffer::RenderBuffer)
            glDeleteRenderbuffers(1, &m_depRboId);
        else if (m_depthAttachment > DepthBuffer::None)
            glDeleteTextures(1, &m_depTexId);
        for (unsigned int i = 0; i < m_colorAttachmentCount; ++i)
            glDeleteTextures(1, m_colTexId + i);
        glDeleteFramebuffers(1, &m_id);
    }

    void Fbo::bind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);
        glViewport(0, 0, m_width, m_height);
    }

    void Fbo::unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

    void Fbo::bindColorAttachmentTexture(int attachment, int slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_colTexId[attachment]);
    }

    void Fbo::bindDepthTexture(int slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_depTexId);
    }

    void create(Vbo &vbo, void *data, unsigned int size) {
        glCreateBuffers(1, &vbo.id);
        glBindBuffer(GL_ARRAY_BUFFER, vbo.id);

        if (data) {
            glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        } else {
            glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
        }
    }
    void destroy(Vbo &vbo) {
        glDeleteBuffers(1, &vbo.id); //
    }
    void bind(const Vbo &vbo) {
        glBindBuffer(GL_ARRAY_BUFFER, vbo.id); //
    }
    void setLayout(Vbo &vbo, const Layout &l) {
        vbo.layout = l; //
    }
    void open(const Vbo &vbo, void *handle) {
        bind(vbo);
        *reinterpret_cast<void **>(handle) = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    }
    void close(const Vbo &vbo) {
        bind(vbo);
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }

    void create(Ibo &ibo, void *data, unsigned int size) {
        glCreateBuffers(1, &ibo.id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo.id);

        if (data) {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        } else {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
        }
    }
    void destroy(Ibo &ibo) {
        glDeleteBuffers(1, &ibo.id); //
    }
    void bind(const Ibo &ibo) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo.id); //
    }
    void open(const Ibo &ibo, void *handle) {
        bind(ibo);
        *reinterpret_cast<void **>(handle) = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
    }

    void close(const Ibo &ibo) {
        bind(ibo);
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    }

    void create(Vao &vao) {
        glGenVertexArrays(1, &vao.id);
        glBindVertexArray(vao.id);
    }

    void destroy(Vao &vao) {
        glDeleteVertexArrays(1, &vao.id); //
    }

    void bind(const Vao &vao) {
        glBindVertexArray(vao.id); //
    }

    void link(Vao &vao, const Vbo &vbo) {
        bind(vao);
        bind(vbo);
        unsigned char *offset = nullptr;
        for (const auto elem : vbo.layout.elements) {
            glEnableVertexAttribArray(vao.attribCount);
            glVertexAttribPointer(vao.attribCount, static_cast<GLint>(elem.count), toOpenGLType(elem.type), GL_FALSE,
                                  static_cast<GLsizei>(vbo.layout.stride), offset);
            offset += elem.getSize();
            ++vao.attribCount;
        }
    }
} // namespace Coel
