#pragma once

#include <Math.hpp>

namespace Coel {
    class Window {
      public:
        Math::Vec2i size;

        struct Mouse {
            Math::Vec2d pos;
            int button, action, mods;
        } mouse;

        struct Key {
            int code, action, mods;
        } key;

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
    };
} // namespace Coel
