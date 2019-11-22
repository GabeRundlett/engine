#pragma once

#include "../core.hpp"
#include "../renderer.hpp"

struct GLFWwindow;

namespace coel {
    class Context {
      public:
        virtual void swap() = 0;
        virtual void bind() = 0;
    };

    namespace opengl {
        class Context final : public coel::Context {
            GLFWwindow *m_window;

          public:
            Context(GLFWwindow *window);
            void swap() override;
            void bind() override;
        };
    } // namespace opengl

    template <typename... Args> static inline Scope<Context> create_context(Args... args) {
        switch (Renderer::get_api()) {
        case RendererAPI::OpenGL: return create_scope<opengl::Context>(args...);
        case RendererAPI::Vulkan:
        case RendererAPI::Direct3D:
        default: return nullptr;
        }
    }
} // namespace coel
