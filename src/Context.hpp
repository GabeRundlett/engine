#pragma once

#include "Core.hpp"
#include "Renderer.hpp"

struct GLFWwindow;

namespace Coel {
    class Context {
      public:
        virtual void swap() = 0;
        virtual void bind() = 0;
    };

    namespace Opengl {
        class Context final : public ::Coel::Context {
            GLFWwindow *mWindow;

          public:
            Context(GLFWwindow *window);
            void swap() override;
            void bind() override;
        };
    } // namespace Opengl

    template <typename... Args> static inline Scope<Context> createContext(Args... args) {
        switch (Renderer::getAPI()) {
        case RendererAPI::OpenGL: return createScope<opengl::Context>(args...);
        case RendererAPI::Vulkan:
        case RendererAPI::Direct3D:
        default: return nullptr;
        }
    }
} // namespace Coel
