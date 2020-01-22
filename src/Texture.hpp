#pragma once

#include "Core.hpp"
#include "Renderer.hpp"

namespace Coel {
    class Texture {
      public:
        virtual void bind(const int slot) const = 0;
        virtual void setData(const unsigned char *const data) const = 0;
    };

    namespace Opengl {
        class Texture final : public ::Coel::Texture {
            const char *const mFilepath;
            unsigned int mId;
            int mWidth, mHeight;
            unsigned int mFormat;

          public:
            Texture(const char *const filepath);
            Texture(const int width, const int height, const unsigned char *const data);
            void bind(const int slot) const override;
            void setData(const unsigned char *const data) const override;
        };
    } // namespace Opengl

    static inline Ref<Texture> createTexture(const char *const filepath) {
        switch (Renderer::getAPI()) {
        case RendererAPI::OPENGL: return createRef<Opengl::Texture>(filepath);
        case RendererAPI::VULKAN:
        case RendererAPI::DIRECT3D:
        default: return nullptr;
        }
    }

    static inline Ref<Texture> createTexture(const int width, const int height, const unsigned char *const data) {
        switch (Renderer::getAPI()) {
        case RendererAPI::OPENGL: return createRef<Opengl::Texture>(width, height, data);
        case RendererAPI::VULKAN:
        case RendererAPI::DIRECT3D:
        default: return nullptr;
        }
    }
} // namespace Coel
