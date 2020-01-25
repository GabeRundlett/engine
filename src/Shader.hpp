#pragma once

#include "Core.hpp"
#include "Renderer.hpp"

namespace Coel {
    class Shader {
      public:
        virtual void bind() const = 0;
        virtual void sendInt(const char *const location, const int value) const = 0;
        virtual void sendInt2(const char *const location, void *data) const = 0;
        virtual void sendInt3(const char *const location, void *data) const = 0;
        virtual void sendInt4(const char *const location, void *data) const = 0;
        virtual void sendFloat(const char *const location, const float value) const = 0;
        virtual void sendFloat2(const char *const location, void *data) const = 0;
        virtual void sendFloat3(const char *const location, void *data) const = 0;
        virtual void sendFloat4(const char *const location, void *data) const = 0;
        virtual void sendMat4(const char *const location, void *data) const = 0;
    };

    namespace Opengl {
        class Shader final : public ::Coel::Shader {
            unsigned int mId;

          public:
            Shader(const char *const vertSrc, const char *const fragSrc);
            void bind() const override;
            void sendInt(const char *const location, const int value) const override;
            void sendInt2(const char *const location, void *data) const override;
            void sendInt3(const char *const location, void *data) const override;
            void sendInt4(const char *const location, void *data) const override;
            void sendFloat(const char *const location, const float value) const override;
            void sendFloat2(const char *const location, void *data) const override;
            void sendFloat3(const char *const location, void *data) const override;
            void sendFloat4(const char *const location, void *data) const override;
            void sendMat4(const char *const location, void *data) const override;
        };
    } // namespace Opengl

    static inline Ref<Shader> createShader(const char *const vertSrc, const char *const fragSrc) {
        switch (Renderer::getAPI()) {
        case RendererAPI::OPENGL: return createRef<Opengl::Shader>(vertSrc, fragSrc);
        case RendererAPI::VULKAN:
        case RendererAPI::DIRECT3D:
        default: return nullptr;
        }
    }
} // namespace Coel
