#pragma once

#include <Math.hpp>
#include "Input.hpp"

namespace Coel {
    class Window {
      public:
        Math::Vec2i size;
        KeyInfo key;
        MouseInfo mouse;
        
        void (*onResize)(Window &w);

        void (*onMouseMove)(Window &w);
        void (*onMouseButton)(Window &w);

        void (*onKey)(Window &w);

        Window() = default;
        Window(int width, int height, const char *const title);
        ~Window();

        int init(int width, int height, const char *const title);
        void update();
        bool isOpen() const;
        void deinit();

        double getTime() const;
        void cursorTo(const Math::Vec2d &pos);
    };
} // namespace Coel
