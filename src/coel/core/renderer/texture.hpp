#pragma once

#include "../core.hpp"
#include "../renderer.hpp"

namespace coel {
    class Texture {
      public:
        virtual void bind(const int slot) const = 0;
        virtual void set_data(const unsigned char *const data) const = 0;
    };

    namespace opengl {
        class Texture final : public coel::Texture {
            const char *const m_filepath;
            unsigned int m_id;
            int m_width, m_height;
            unsigned int m_format;

          public:
            Texture(const char *const filepath);
            Texture(const int width, const int height, const unsigned char *const data);
            void bind(const int slot) const override;
            void set_data(const unsigned char *const data) const override;
        };
    } // namespace opengl

    static inline Ref<Texture> create_texture(const char *const filepath) {
        switch (Renderer::get_api()) {
        case RendererAPI::OpenGL: return create_ref<opengl::Texture>(filepath);
        case RendererAPI::Vulkan:
        case RendererAPI::Direct3D:
        default: return nullptr;
        }
    }

    static inline Ref<Texture> create_texture(const int width, const int height, const unsigned char *const data) {
        switch (Renderer::get_api()) {
        case RendererAPI::OpenGL: return create_ref<opengl::Texture>(width, height, data);
        case RendererAPI::Vulkan:
        case RendererAPI::Direct3D:
        default: return nullptr;
        }
    }
} // namespace coel
