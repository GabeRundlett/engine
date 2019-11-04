#pragma once

namespace coel {
    enum class ColorSpace : const unsigned char { RGB, RGBA };
    struct Texture {
        unsigned int id;
        int width, height;
        ColorSpace color_space;
        const char *filepath;
    };
    namespace texture {
        Texture create(const char *const filepath);
        Texture create(const int width, const int height, const ColorSpace space);
        void update(const Texture &t, const void *const data);
    } // namespace texture
} // namespace coel
