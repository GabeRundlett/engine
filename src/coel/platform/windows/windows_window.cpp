#include "../../core/window.hpp"
#include "../../core/renderer.hpp"

#define GLFW_INCLUDE_NONE 1
#include <GLFW/glfw3.h>

#include <debug.hpp>

namespace coel { namespace windows {
    namespace default_callbacks {
        static void key_press(const KeyPress &) {}
        static void key_repeat(const KeyRepeat &) {}
        static void key_release(const KeyRelease &) {}

        static void mouse_press(const MousePress &) {}
        static void mouse_release(const MouseRelease &) {}
        static void mouse_move(const MouseMove &) {}
        static void mouse_scroll(const MouseScroll &) {}

        static void window_move(const WindowMove &) {}
        static void window_resize(const WindowResize &) {}
        static void window_focus(const WindowFocus &) {}
        static void window_defocus(const WindowDefocus &) {}
        static void window_close(const WindowClose &) {}
    } // namespace default_callbacks

    Window::Window(const int width, const int height, const char *const title)
        : m_key_press_callback(default_callbacks::key_press), m_key_repeat_callback(default_callbacks::key_repeat),
          m_key_release_callback(default_callbacks::key_release), m_mouse_press_callback(default_callbacks::mouse_press),
          m_mouse_release_callback(default_callbacks::mouse_release), m_mouse_move_callback(default_callbacks::mouse_move),
          m_mouse_scroll_callback(default_callbacks::mouse_scroll), m_window_move_callback(default_callbacks::window_move),
          m_window_resize_callback(default_callbacks::window_resize), m_window_focus_callback(default_callbacks::window_focus),
          m_window_defocus_callback(default_callbacks::window_defocus),
          m_window_close_callback(default_callbacks::window_close) {

        SCOPED_PROFILE;

        glfwInit();
        {
            ::debug::profile::ScopedProfile profile("glfwCreateWindow");
            m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        }

        Renderer::set_api(RendererAPI::OpenGL);
        m_context = create_context(m_window);
        Renderer::init();

        glfwSwapInterval(0);

        glfwSetWindowUserPointer(m_window, this);
        glfwSetKeyCallback(m_window, [](GLFWwindow *w, int key, int scancode, int action, int mods) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            switch (action) {
            case GLFW_PRESS: window->m_key_press_callback({key, scancode, mods}); break;
            case GLFW_REPEAT: window->m_key_repeat_callback({key, scancode, mods}); break;
            case GLFW_RELEASE: window->m_key_release_callback({key, scancode, mods}); break;
            }
        });
        glfwSetMouseButtonCallback(m_window, [](GLFWwindow *w, int button, int action, int mods) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            switch (action) {
            case GLFW_PRESS: window->m_mouse_press_callback({button, mods}); break;
            case GLFW_RELEASE: window->m_mouse_release_callback({button, mods}); break;
            }
        });
        glfwSetCursorPosCallback(m_window, [](GLFWwindow *w, double xPos, double yPos) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            window->m_mouse_move_callback({xPos, yPos});
        });
        glfwSetScrollCallback(m_window, [](GLFWwindow *w, double xOffset, double yOffset) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            window->m_mouse_scroll_callback({xOffset, yOffset});
        });
        glfwSetWindowPosCallback(m_window, [](GLFWwindow *w, int xPos, int yPos) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            window->m_window_move_callback({xPos, yPos});
        });
        glfwSetWindowSizeCallback(m_window, [](GLFWwindow *w, int width, int height) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            Renderer::set_viewport(0, 0, width, height);
            window->m_width = width, window->m_height = height;
            window->m_window_resize_callback({width, height});
        });
        glfwSetWindowFocusCallback(m_window, [](GLFWwindow *w, int focus) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            switch (focus) {
            case GLFW_TRUE: window->m_window_focus_callback({}); return;
            case GLFW_FALSE: window->m_window_defocus_callback({}); return;
            }
        });
        glfwSetWindowCloseCallback(m_window, [](GLFWwindow *w) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            window->m_window_close_callback({});
        });
    }

    Window::~Window() { debug::profile::end(); }

    void Window::on_key_press(void (*const f)(const KeyPress &)) { m_key_press_callback = f; }
    void Window::on_key_repeat(void (*const f)(const KeyRepeat &)) { m_key_repeat_callback = f; }
    void Window::on_key_release(void (*const f)(const KeyRelease &)) { m_key_release_callback = f; }

    void Window::on_mouse_press(void (*const f)(const MousePress &)) { m_mouse_press_callback = f; };
    void Window::on_mouse_release(void (*const f)(const MouseRelease &)) { m_mouse_release_callback = f; };
    void Window::on_mouse_move(void (*const f)(const MouseMove &)) { m_mouse_move_callback = f; };
    void Window::on_mouse_scroll(void (*const f)(const MouseScroll &)) { m_mouse_scroll_callback = f; };

    void Window::on_window_move(void (*const f)(const WindowMove &)) { m_window_move_callback = f; };
    void Window::on_window_resize(void (*const f)(const WindowResize &)) { m_window_resize_callback = f; };
    void Window::on_window_focus(void (*const f)(const WindowFocus &)) { m_window_focus_callback = f; };
    void Window::on_window_defocus(void (*const f)(const WindowDefocus &)) { m_window_defocus_callback = f; };
    void Window::on_window_close(void (*const f)(const WindowClose &)) { m_window_close_callback = f; };

    bool Window::is_open() const { return !glfwWindowShouldClose(m_window); }

    void Window::update() {
        SCOPED_PROFILE;

        m_context->swap();
        glfwPollEvents();
    }
}} // namespace coel::windows
