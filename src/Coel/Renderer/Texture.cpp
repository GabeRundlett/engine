#include "Texture.hpp"

#include <glad/glad.h>
#include <stb.hpp>

namespace Coel {
    static inline void toOpenGLColorFormat(unsigned char attachment, GLenum data[3]) {
        switch (attachment) {
        case Format::RGB8: data[0] = GL_RGB8, data[1] = GL_RGB, data[2] = GL_UNSIGNED_BYTE; return;
        case Format::RGBA8: data[0] = GL_RGBA8, data[1] = GL_RGBA, data[2] = GL_UNSIGNED_BYTE; return;
        case Format::RGB32F: data[0] = GL_RGB32F, data[1] = GL_RGB, data[2] = GL_FLOAT; return;
        }
    }
    static inline auto toOpenGLFilterMode(unsigned char mode) {
        switch (mode) {
        case Filter::Nearest: return GL_NEAREST;
        case Filter::Linear: return GL_LINEAR;
        default: return GL_NEAREST;
        }
    }
    static inline auto toOpenGLWrapMode(unsigned char mode) {
        switch (mode) {
        case Wrap::Repeat: return GL_REPEAT;
        case Wrap::ClampToEdge: return GL_CLAMP_TO_EDGE;
        case Wrap::ClampToBorder: return GL_CLAMP_TO_BORDER;
        default: return GL_REPEAT;
        }
    }

    Texture::Texture(const char *const filepath) {
        stbi_set_flip_vertically_on_load(true);
        int channels;
        stbi_uc *data = stbi_load(filepath, &m_width, &m_height, &channels, 0);
        switch (channels) {
        case 3: toOpenGLColorFormat(Format::RGB8, m_formatData); break;
        case 4: toOpenGLColorFormat(Format::RGBA8, m_formatData); break;
        default: break;
        }
        glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
        glTextureStorage2D(m_id, 1, m_formatData[0], m_width, m_height);
        glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, m_formatData[1], m_formatData[2], data);
        stbi_image_free(data);
    }

    Texture::Texture(const int width, const int height, unsigned char format, const unsigned char *const data)
        : m_width(width), m_height(height) {
        toOpenGLColorFormat(format, m_formatData);
        glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
        glTextureStorage2D(m_id, 1, m_formatData[0], m_width, m_height);
        if (data != nullptr) glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, m_formatData[1], m_formatData[2], data);
    }

    void Texture::bind(const int slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

    void Texture::setData(const unsigned char *const data) const {
        glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, m_formatData[1], m_formatData[2], data);
    }

    void Texture::setMinFilter(const unsigned char mode) {
        auto filterMode = toOpenGLFilterMode(mode);
        glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, filterMode);
    }
    void Texture::setMagFilter(const unsigned char mode) {
        auto filterMode = toOpenGLFilterMode(mode);
        glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, filterMode);
    }
    void Texture::setWrap(const unsigned char mode) {
        auto wrapMode = toOpenGLWrapMode(mode);
        glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, wrapMode);
        glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, wrapMode);
    }
} // namespace Coel
