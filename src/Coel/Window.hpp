#pragma once

#include <Math.hpp>
#include "Input.hpp"

struct GLFWwindow;

namespace Coel {
    class Window {
      public:
        enum CursorMode {
            Normal,
            Hidden,
            Disabled,
        };

        Math::Vec2i size;
        KeyInfo key;
        MouseInfo mouse;

        void (*onMouseScroll)(Window &w), (*onMouseMove)(Window &w), (*onMouseButton)(Window &w), (*onResize)(Window &w),
            (*onKey)(Window &w);

        Window() = default;
        Window(int width, int height, const char *const title);
        ~Window();

        int init(int width, int height, const char *const title);
        void update();
        bool isOpen() const;
        void deinit();
        void close();
        void resize();

        double getTime() const;
        void cursorTo(const Math::Vec2d &pos);
        void cursorMode(const unsigned int mode);
        GLFWwindow *getGlfwWindow();
    };
} // namespace Coel
