#pragma once

#include <Coel/Window.hpp>
#include <imgui.h>

namespace Coel { namespace Renderer {
    class ImGuiRenderer {
      public:
        ImGuiRenderer(Window &window);
        void begin() const;
        void end(Window &window) const;
    };
}} // namespace Coel::Renderer
