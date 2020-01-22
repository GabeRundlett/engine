#include "Common.hpp"
#include "../Texture.hpp"

#include <stb.hpp>

namespace Coel { namespace Opengl {
    Texture::Texture(const char *const filepath) : mFilepath(filepath), mFormat(0) {
        // DEBUG_BEGIN_FUNC_PROFILE;

        stbi_set_flip_vertically_on_load(true);
        int channels;
        GLenum tStorageFormat = 0;
        stbi_uc *data = stbi_load(filepath, &mWidth, &mHeight, &channels, 0);
        switch (channels) {
        case 3: mFormat = GL_RGB, tStorageFormat = GL_RGB8; break;
        case 4: mFormat = GL_RGBA, tStorageFormat = GL_RGBA8; break;
        default: break; // UNSUPPORTED FORMAT!
        }

        GL_CALL(glCreateTextures(GL_TEXTURE_2D, 1, &mId));
        GL_CALL(glTextureStorage2D(mId, 1, tStorageFormat, mWidth, mHeight));

        GL_CALL(glTextureParameteri(mId, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL_CALL(glTextureParameteri(mId, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

        GL_CALL(glTextureParameteri(mId, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GL_CALL(glTextureParameteri(mId, GL_TEXTURE_WRAP_T, GL_REPEAT));

        GL_CALL(glTextureSubImage2D(mId, 0, 0, 0, mWidth, mHeight, mFormat, GL_UNSIGNED_BYTE, data));

        stbi_image_free(data);
    }

    Texture::Texture(const int width, const int height, const unsigned char *const data)
        : mFilepath(nullptr), mWidth(width), mHeight(height), mFormat(GL_RGBA) {
        // DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(glCreateTextures(GL_TEXTURE_2D, 1, &mId));
        GL_CALL(glTextureStorage2D(mId, 1, GL_RGBA8, mWidth, mHeight));

        GL_CALL(glTextureParameteri(mId, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL_CALL(glTextureParameteri(mId, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

        GL_CALL(glTextureParameteri(mId, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GL_CALL(glTextureParameteri(mId, GL_TEXTURE_WRAP_T, GL_REPEAT));

        if (data != nullptr) { GL_CALL(glTextureSubImage2D(mId, 0, 0, 0, mWidth, mHeight, mFormat, GL_UNSIGNED_BYTE, data)); }
    }

    void Texture::bind(const int slot) const {
        // DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(glBindTextureUnit(slot, mId));
    }

    void Texture::setData(const unsigned char *const data) const {
        // DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(glTextureSubImage2D(mId, 0, 0, 0, mWidth, mHeight, mFormat, GL_UNSIGNED_BYTE, data));
    }
}} // namespace Coel::Opengl
