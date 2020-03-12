#include "Texture.hpp"

#include <glad/glad.h>
#include <stb.hpp>

namespace Coel {
    Texture::Texture(const char *const filepath) : m_format(0) {
        stbi_set_flip_vertically_on_load(true);
        
        int channels;
        GLenum tStorageFormat = 0;
        stbi_uc *data = stbi_load(filepath, &m_width, &m_height, &channels, 0);

        switch (channels) {
        case 3: m_format = GL_RGB, tStorageFormat = GL_RGB8; break;
        case 4: m_format = GL_RGBA, tStorageFormat = GL_RGBA8; break;
        default: break; 
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
        glTextureStorage2D(m_id, 1, tStorageFormat, m_width, m_height);

        glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, m_format, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    Texture::Texture(const int width, const int height, const unsigned char *const data)
        : m_width(width), m_height(height), m_format(GL_RGBA) {
        glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
        glTextureStorage2D(m_id, 1, GL_RGBA8, m_width, m_height);

        glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

        if (data != nullptr) { glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, m_format, GL_UNSIGNED_BYTE, data); }
    }

    void Texture::bind(const int slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_id);
        // glBindTextureUnit(slot, m_id);
    }

    void Texture::setData(const unsigned char *const data) const {
        glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, m_format, GL_UNSIGNED_BYTE, data);
    }
}
