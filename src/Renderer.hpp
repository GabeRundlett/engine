#pragma once

namespace Coel {
    enum class RendererAPI : unsigned char { NONE, OPENGL, VULKAN, DIRECT3D };

    namespace Opengl {
        void init();
        void clear();
        void setClearColor(float r, float g, float b, float a);
        void setViewportSize(int x, int y, int width, int height);
    } // namespace Opengl

    class Renderer {
        static inline RendererAPI sRendererAPI = RendererAPI::NONE;

      public:
        static RendererAPI getAPI() { return sRendererAPI; }
        static void setAPI(const RendererAPI &api) { sRendererAPI = api; }
        static inline void init() {
            switch (sRendererAPI) {
            case RendererAPI::NONE:
            case RendererAPI::OPENGL: Opengl::init(); break;
            case RendererAPI::VULKAN:
            case RendererAPI::DIRECT3D:
            default: break;
            }
        }
        static inline void clear() {
            switch (sRendererAPI) {
            case RendererAPI::NONE:
            case RendererAPI::OPENGL: Opengl::clear(); break;
            case RendererAPI::VULKAN:
            case RendererAPI::DIRECT3D:
            default: break;
            }
        }
        static inline void set_clear_color(float r, float g, float b, float a) {
            switch (sRendererAPI) {
            case RendererAPI::NONE:
            case RendererAPI::OPENGL: Opengl::setClearColor(r, g, b, a); break;
            case RendererAPI::VULKAN:
            case RendererAPI::DIRECT3D:
            default: break;
            }
        }
        static inline void set_viewport(int x, int y, int width, int height) {
            switch (sRendererAPI) {
            case RendererAPI::NONE:
            case RendererAPI::OPENGL: Opengl::setViewportSize(x, y, width, height); break;
            case RendererAPI::VULKAN:
            case RendererAPI::DIRECT3D:
            default: break;
            }
        }
    };
} // namespace Coel
