#include "../coel.hpp"
#include <glad/glad.h>
#include <stb/image.hpp>

namespace coel {
    static unsigned int s_texture_count = 0;

    namespace texture {
        Texture create(const char *const filepath) {
            // stbi_set_flip_vertically_on_load(true);
            unsigned int id;
            int width, height, channels;
            ColorSpace space;
            unsigned char *data = stbi_load(filepath, &width, &height, &channels, 0);

            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            switch (channels) {
            case 3:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                space = ColorSpace::RGB;
                break;
            case 4:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                space = ColorSpace::RGBA;
                break;
            default:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                space = ColorSpace::RGBA;
                break;
            }
            glGenerateMipmap(GL_TEXTURE_2D);

            stbi_image_free(data);
            ++s_texture_count;
            return {id, width, height, space, filepath};
        }
        Texture create(const int width, const int height, const ColorSpace space) {
            unsigned int id;
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            switch (space) {
            case ColorSpace::RGB:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
                break;
            case ColorSpace::RGBA:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
                break;
            default: glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr); break;
            }
            return {id, width, height, space, nullptr};
        }
        void update(const Texture &t, const void *const data) {
            glBindTexture(GL_TEXTURE_2D, t.id);
            switch (t.color_space) {
            case ColorSpace::RGB:
                glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, t.width, t.height, GL_RGB, GL_UNSIGNED_BYTE, data);
                break;
            case ColorSpace::RGBA:
                glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, t.width, t.height, GL_RGBA, GL_UNSIGNED_BYTE, data);
                break;
            default: glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, t.width, t.height, GL_RGBA, GL_UNSIGNED_BYTE, data); break;
            }
        }
    } // namespace texture
} // namespace coel
