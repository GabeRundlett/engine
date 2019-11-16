#pragma once

namespace coel {
    enum class RendererAPI : unsigned char { OpenGL, Vulkan, Direct3D, None };

    namespace opengl {
        void init();
        void clear();
        void set_clear_color(float r, float g, float b, float a);
        void set_viewport(float x, float y, float width, float height);
    } // namespace opengl

    class Renderer {
        static inline RendererAPI s_renderer_api = RendererAPI::None;

      public:
        static RendererAPI get_api() { return s_renderer_api; }
        static void set_api(const RendererAPI api) { s_renderer_api = api; }
        static inline void init() {
            switch (s_renderer_api) {
            case RendererAPI::OpenGL: opengl::init(); break;
            case RendererAPI::Vulkan:
            case RendererAPI::Direct3D:
            case RendererAPI::None:
            default: break;
            }
        }
        static inline void clear() {
            switch (s_renderer_api) {
            case RendererAPI::OpenGL: opengl::clear(); break;
            case RendererAPI::Vulkan:
            case RendererAPI::Direct3D:
            case RendererAPI::None:
            default: break;
            }
        }
        static inline void set_clear_color(float r, float g, float b, float a) {
            switch (s_renderer_api) {
            case RendererAPI::OpenGL: opengl::set_clear_color(r, g, b, a); break;
            case RendererAPI::Vulkan:
            case RendererAPI::Direct3D:
            case RendererAPI::None:
            default: break;
            }
        }
        static inline void set_viewport(float x, float y, float width, float height) {
            switch (s_renderer_api) {
            case RendererAPI::OpenGL: opengl::set_viewport(x, y, width, height); break;
            case RendererAPI::Vulkan:
            case RendererAPI::Direct3D:
            case RendererAPI::None:
            default: break;
            }
        }
    };
} // namespace coel
