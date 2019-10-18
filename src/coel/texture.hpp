#pragma once

namespace coel {
    enum class ColorSpace : const unsigned char { RGB, RGBA };
    struct Texture {
        unsigned int id;
        int width, height;
        ColorSpace color_space;
        const char *filepath;
    };
    namespace _internal {
        Texture create(const char *const filepath);
        Texture create(const int width, const int height, const ColorSpace space);
    } // namespace _internal
    void update(const Texture &t, const void *const data);
} // namespace coel
