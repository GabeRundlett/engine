#pragma once

namespace coel {
    enum class RendererAPI : unsigned char { OpenGL, Direct3D, Vulkan, None };

    class Renderer {
        static inline RendererAPI s_renderer_api = RendererAPI::None;

      public:
        static RendererAPI get_api() { return s_renderer_api; }
        static void set_api(const RendererAPI api) { s_renderer_api = api; }
    };
} // namespace coel
