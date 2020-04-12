#include "Buffer.hpp"
#include "Texture.hpp"

#include <glad/glad.h>

namespace Coel {
    static inline constexpr GLenum toGlType(ElementType type) {
        switch (type) {
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

    void create(Vbo &vbo, void *data, const uint32_t size) {
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
    void open(const Vbo &vbo, void *handle) {
        bind(vbo);
        *reinterpret_cast<void **>(handle) = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    }
    void close(const Vbo &vbo) {
        bind(vbo);
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }

    void create(Ibo &ibo, void *data, const uint32_t size) {
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
        uint8_t *offset = nullptr;
        for (const auto elem : vbo.layout.elements) {
            glEnableVertexAttribArray(vao.attribCount);
            glVertexAttribPointer(vao.attribCount, static_cast<GLint>(elem.count), toGlType(elem.type), GL_FALSE,
                                  static_cast<GLsizei>(vbo.layout.stride), offset);
            offset += elem.getSize();
            ++vao.attribCount;
        }
    }

    void create(Rbo &rbo, const glm::ivec2 &size) {
        rbo.size = size;
        glGenRenderbuffers(1, &rbo.id);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo.id);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.x, size.y);
    }
    void destroy(Rbo &rbo) {
        glDeleteRenderbuffers(1, &rbo.id); //
    }

    void create(Fbo &fbo, const glm::ivec2 &size) {
        fbo.size = size;
        glGenFramebuffers(1, &fbo.id);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo.id);
    }
    void bind(const Fbo &fbo) {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo.id);
        glViewport(0, 0, fbo.size.x, fbo.size.y);
    }
    void attach(Fbo &fbo, const std::initializer_list<Texture> &attachments) {
        bind(fbo);
        GLenum glAttachmentType{};
        uint32_t colAttachmentCount{}, colAttachmentId{};
        for (auto &attachment : attachments)
            if (attachment.fmtData[0] != GL_DEPTH_COMPONENT) ++colAttachmentCount;
        GLenum drawBuffers[]{
            GL_COLOR_ATTACHMENT0,
            GL_COLOR_ATTACHMENT1,
            GL_COLOR_ATTACHMENT2,
            GL_COLOR_ATTACHMENT3,
        };

        if (colAttachmentCount < 5) {
            glDrawBuffers(colAttachmentCount, drawBuffers);
            for (auto &attachment : attachments) {
                glAttachmentType = GL_DEPTH_ATTACHMENT;
                if (attachment.fmtData[0] != GL_DEPTH_COMPONENT) {
                    glAttachmentType = drawBuffers[colAttachmentId];
                    ++colAttachmentId;
                }
                glFramebufferTexture2D(GL_FRAMEBUFFER, glAttachmentType, GL_TEXTURE_2D, attachment.id, 0);
            }
        }
    }
    void attach(Fbo &fbo, const Rbo &rbo) {
        bind(fbo);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo.id);
    }
    void destroy(Fbo &fbo) {
        glDeleteFramebuffers(1, &fbo.id); //
    }
} // namespace Coel
