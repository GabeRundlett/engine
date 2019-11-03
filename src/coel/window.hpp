#pragma once

namespace coel {
    struct Window {
        unsigned int width, height;
        const char *title;
        void *window_handle;
        math::Vec2 mouse = {0, 0};
        Window() = default;
        Window(const unsigned int width, const unsigned int height, const char *const title);
        void init(const unsigned int width, const unsigned int height, const char *const title);
        void update();
        void make_current();
        bool should_close();
        float get_time();
        virtual void on_update() {}
        virtual void key_press(const KeyPress &e) {}
        virtual void key_repeat(const KeyRepeat &e) {}
        virtual void key_release(const KeyRelease &e) {}
        virtual void mouse_press(const MousePress &e) {}
        virtual void mouse_release(const MouseRelease &e) {}
        virtual void mouse_scroll(const MouseScroll &e) {}
        virtual void mouse_move(const MouseMove &e) {}
        virtual void window_move(const WindowMove &e) {}
        virtual void window_resize(const WindowResize &e) {}
        virtual void window_close(const WindowClose &e) {}
        virtual void window_focus(const WindowFocus &e) {}
        virtual void window_defocus(const WindowDefocus &e) {}
    };
} // namespace coel
