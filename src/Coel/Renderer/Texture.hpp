#pragma once

#include <glm/glm.hpp>

namespace Coel {
    enum TextureFormat {
        RED,
        REDF,
        RGB,
        RGBA,
        RGB16F,
        RGBA16F,
        RGB32F,
        RGBA32F,
        Depth,
    };
    enum TextureFilter {
        Linear,
        Nearest,
    };
    enum TextureWrap {
        ClampToEdge,
        ClampToBorder,
        Repeat,
    };

    struct Texture {
        glm::ivec2 size{};
        uint32_t id{}, fmtData[3]{};
    };

    void create(Texture &tex, const char *const filepath);
    void create(Texture &tex, const glm::ivec2 &size, const TextureFormat format, const uint8_t *const data);
    void bind(const Texture &tex, const int32_t slot);
    void setData(const Texture &tex, const uint8_t *const data);
    void setMinFilter(Texture &tex, TextureFilter mode);
    void setMagFilter(Texture &tex, TextureFilter mode);
    void setWrapMode(Texture &tex, TextureWrap mode);
    void destroy(Texture &tex);
} // namespace Coel
