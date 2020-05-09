#include "Texture.hpp"

#include <glad/glad.h>
#include <stb.hpp>

namespace Coel {
    static inline void toGlFormat(const TextureFormat format, uint32_t fmtData[3]) {
        switch (format) {
        case RED: fmtData[0] = GL_RED, fmtData[1] = GL_RED, fmtData[2] = GL_UNSIGNED_BYTE; break;
        case REDF: fmtData[0] = GL_RED, fmtData[1] = GL_RED, fmtData[2] = GL_FLOAT; break;
        case RGB: fmtData[0] = GL_RGB8, fmtData[1] = GL_RGB, fmtData[2] = GL_UNSIGNED_BYTE; break;
        case RGBA: fmtData[0] = GL_RGBA8, fmtData[1] = GL_RGBA, fmtData[2] = GL_UNSIGNED_BYTE; break;
        case RGB16F: fmtData[0] = GL_RGB16F, fmtData[1] = GL_RGB, fmtData[2] = GL_FLOAT; break;
        case RGBA16F: fmtData[0] = GL_RGBA16F, fmtData[1] = GL_RGBA, fmtData[2] = GL_FLOAT; break;
        case RGB32F: fmtData[0] = GL_RGB32F, fmtData[1] = GL_RGB, fmtData[2] = GL_FLOAT; break;
        case RGBA32F: fmtData[0] = GL_RGBA32F, fmtData[1] = GL_RGBA, fmtData[2] = GL_FLOAT; break;
        case Depth: fmtData[0] = GL_DEPTH_COMPONENT, fmtData[1] = GL_DEPTH_COMPONENT, fmtData[2] = GL_FLOAT; break;
        default: break;
        }
    }

    static inline constexpr GLenum toGlFilter(const TextureFilter mode) {
        switch (mode) {
        case Linear: return GL_LINEAR;
        default: return GL_NEAREST;
        }
    }
    static inline constexpr GLenum toGlWrap(const TextureWrap mode) {
        switch (mode) {
        case ClampToEdge: return GL_CLAMP_TO_EDGE;
        case ClampToBorder: return GL_CLAMP_TO_BORDER;
        default: return GL_REPEAT;
        }
    }

    void create(Texture &tex, const char *const filepath) {
        int32_t channels;
        stbi_set_flip_vertically_on_load(true);
        stbi_uc *data = stbi_load(filepath, &tex.size.x, &tex.size.y, &channels, 0);
        TextureFormat format{};
        switch (channels) {
        case 1: format = RED; break;
        case 3: format = RGB; break;
        case 4: format = RGBA; break;
        default: break;
        }
        create(tex, tex.size, format, data);
        stbi_image_free(data);
    }

    void create(Texture &tex, const glm::ivec2 &size, const TextureFormat format, const unsigned char *const data) {
        tex.size = size;
        toGlFormat(format, tex.fmtData);
        glCreateTextures(GL_TEXTURE_2D, 1, &tex.id);
        glBindTexture(GL_TEXTURE_2D, tex.id);
        glTextureStorage2D(tex.id, 1, tex.fmtData[0], tex.size.x, tex.size.y);
        if (data != nullptr)
            setData(tex, data);
    }

    void bind(const Texture &tex, const int32_t slot) {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, tex.id);
    }

    void setData(const Texture &tex, const uint8_t *const data) {
        glTextureSubImage2D(tex.id, 0, 0, 0, tex.size.x, tex.size.y, tex.fmtData[1], tex.fmtData[2], data);
    }

    void setMinFilter(Texture &tex, const TextureFilter mode) {
        glTextureParameteri(tex.id, GL_TEXTURE_MIN_FILTER, toGlFilter(mode));
    }
    void setMagFilter(Texture &tex, const TextureFilter mode) {
        glTextureParameteri(tex.id, GL_TEXTURE_MAG_FILTER, toGlFilter(mode));
    }
    void setWrapMode(Texture &tex, const TextureWrap mode) {
        glTextureParameteri(tex.id, GL_TEXTURE_WRAP_S, toGlWrap(mode));
        glTextureParameteri(tex.id, GL_TEXTURE_WRAP_T, toGlWrap(mode));
    }
    void destroy(Texture &tex) {
        glDeleteTextures(1, &tex.id); //
    }
} // namespace Coel
