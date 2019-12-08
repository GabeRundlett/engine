#pragma once

#include "core.hpp"
#include "events.hpp"
#include "renderer/context.hpp"

namespace coel {
    class Window {
      public:
        virtual bool should_close() const = 0;
        virtual bool is_open() const = 0;
        virtual void update() = 0;
        virtual void bind() = 0;
        virtual void close() = 0;

        virtual void on_key_press(void (*const f)(const KeyPress &)) = 0;
        virtual void on_key_repeat(void (*const f)(const KeyRepeat &)) = 0;
        virtual void on_key_release(void (*const f)(const KeyRelease &)) = 0;
        virtual void on_mouse_press(void (*const f)(const MousePress &)) = 0;
        virtual void on_mouse_release(void (*const f)(const MouseRelease &)) = 0;
        virtual void on_mouse_move(void (*const f)(const MouseMove &)) = 0;
        virtual void on_mouse_scroll(void (*const f)(const MouseScroll &)) = 0;
        virtual void on_window_move(void (*const f)(const WindowMove &)) = 0;
        virtual void on_window_resize(void (*const f)(const WindowResize &)) = 0;
        virtual void on_window_focus(void (*const f)(const WindowFocus &)) = 0;
        virtual void on_window_defocus(void (*const f)(const WindowDefocus &)) = 0;
        virtual void on_window_close(void (*const f)(const WindowClose &)) = 0;
    };

    namespace windows {
        class Window final : public coel::Window {
            GLFWwindow *m_window;
            Scope<Context> m_context;
            int m_width, m_height;
            bool m_is_open;

            void (*m_key_press_callback)(const KeyPress &);
            void (*m_key_repeat_callback)(const KeyRepeat &);
            void (*m_key_release_callback)(const KeyRelease &);

            void (*m_mouse_press_callback)(const MousePress &);
            void (*m_mouse_release_callback)(const MouseRelease &);
            void (*m_mouse_move_callback)(const MouseMove &);
            void (*m_mouse_scroll_callback)(const MouseScroll &);

            void (*m_window_move_callback)(const WindowMove &);
            void (*m_window_resize_callback)(const WindowResize &);
            void (*m_window_focus_callback)(const WindowFocus &);
            void (*m_window_defocus_callback)(const WindowDefocus &);
            void (*m_window_close_callback)(const WindowClose &);

          public:
            Window(const int width, const int height, const char *const title);
            ~Window();
            bool should_close() const override;
            bool is_open() const override { return m_is_open; }
            void update() override;
            void bind() override;
            void close() override;

            void on_key_press(void (*const f)(const KeyPress &)) override;
            void on_key_repeat(void (*const f)(const KeyRepeat &)) override;
            void on_key_release(void (*const f)(const KeyRelease &)) override;

            void on_mouse_press(void (*const f)(const MousePress &)) override;
            void on_mouse_release(void (*const f)(const MouseRelease &)) override;
            void on_mouse_move(void (*const f)(const MouseMove &)) override;
            void on_mouse_scroll(void (*const f)(const MouseScroll &)) override;

            void on_window_move(void (*const f)(const WindowMove &)) override;
            void on_window_resize(void (*const f)(const WindowResize &)) override;
            void on_window_focus(void (*const f)(const WindowFocus &)) override;
            void on_window_defocus(void (*const f)(const WindowDefocus &)) override;
            void on_window_close(void (*const f)(const WindowClose &)) override;
        };
    } // namespace windows

    static inline Ref<Window> create_window(const unsigned int width, const unsigned int height, const char *const frag_src) {
#if _WIN64 || _WIN32
        return create_ref<windows::Window>(width, height, frag_src);
#elif __linux__
        return nullptr;
#elif __APPLE__ && __MACH__
        return nullptr;
#endif
    }
} // namespace coel
