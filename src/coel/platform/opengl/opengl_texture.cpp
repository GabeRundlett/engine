#include "../../core/renderer/texture.hpp"
#include "common.hpp"

#include <stb.hpp>

#include <debug.hpp>

namespace coel { namespace opengl {
    Texture::Texture(const char *const filepath) : m_filepath(filepath), m_format(0) {
        SCOPED_PROFILE;

        stbi_set_flip_vertically_on_load(true);
        int channels;
        GLenum storage_format = 0;
        stbi_uc *data = stbi_load(filepath, &m_width, &m_height, &channels, 0);
        switch (channels) {
        case 3: m_format = GL_RGB, storage_format = GL_RGB8; break;
        case 4: m_format = GL_RGBA, storage_format = GL_RGBA8; break;
        default: break; // UNSUPPORTED FORMAT!
        }

        GL_CALL(glCreateTextures(GL_TEXTURE_2D, 1, &m_id));
        GL_CALL(glTextureStorage2D(m_id, 1, storage_format, m_width, m_height));

        GL_CALL(glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL_CALL(glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

        GL_CALL(glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GL_CALL(glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT));

        GL_CALL(glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, m_format, GL_UNSIGNED_BYTE, data));

        stbi_image_free(data);
    }

    Texture::Texture(const int width, const int height, const unsigned char *const data)
        : m_filepath(nullptr), m_width(width), m_height(height), m_format(GL_RGBA) {
        SCOPED_PROFILE;

        GL_CALL(glCreateTextures(GL_TEXTURE_2D, 1, &m_id));
        GL_CALL(glTextureStorage2D(m_id, 1, GL_RGBA8, m_width, m_height));

        GL_CALL(glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL_CALL(glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

        GL_CALL(glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GL_CALL(glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT));

        GL_CALL(glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, m_format, GL_UNSIGNED_BYTE, data));
    }

    void Texture::bind(const int slot) const {
        SCOPED_PROFILE;

        GL_CALL(glBindTextureUnit(slot, m_id));
    }

    void Texture::set_data(const unsigned char *const data) const {
        SCOPED_PROFILE;

        GL_CALL(glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, m_format, GL_UNSIGNED_BYTE, data));
    }
}} // namespace coel::opengl
