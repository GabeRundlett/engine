#pragma once
#include "event.hpp"
#include "renderer.hpp"

#ifdef COEL_SET_DEFAULT_WINDOW_API_GLFW
#define _COEL_DEFAULT_WINDOW_API GLFW
#endif
#ifdef COEL_SET_DEFAULT_WINDOW_API_WIN32
#define _COEL_DEFAULT_WINDOW_API Win32
#endif
#ifdef COEL_SET_DEFAULT_WINDOW_API_AGNOSTIC
#define _COEL_DEFAULT_WINDOW_API Agnostic
#endif
#ifndef _COEL_DEFAULT_WINDOW_API
#ifdef _CONFIG_PLATFORM_WINDOWS
#define _COEL_DEFAULT_WINDOW_API Win32
#else
#ifdef _CONFIG_PLATFORM_LINUX
#define _COEL_DEFAULT_WINDOW_API GLFW
#else
#define _COEL_DEFAULT_WINDOW_API Agnostic
#endif
#endif
#endif

namespace coel {
enum class WindowAPI { None, Agnostic, Win32, GLFW };
struct Window {
    WindowAPI window_api;
    RendererAPI renderer_api;
    void *handle;
    int width, height;
};
} // namespace coel

//
//
//
//
//

namespace coel { namespace window { namespace _internal {
    namespace agnostic {
        namespace callback { namespace set {
            namespace mouse {
                void press(void (*const func)(const coel::mouse::Press &));
                void release(void (*const func)(const coel::mouse::Release &));
                void scroll(void (*const func)(const coel::mouse::Scroll &));
                void move(void (*const func)(const coel::mouse::Move &));
            } // namespace mouse
            namespace key {
                void press(void (*const func)(const coel::key::Press &));
                void repeat(void (*const func)(const coel::key::Repeat &));
                void release(void (*const func)(const coel::key::Release &));
            } // namespace key
            namespace window {
                void move(void (*const func)(const coel::window::Move &));
                void resize(void (*const func)(const coel::window::Resize &));
                void close(void (*const func)(const coel::window::Close &));
                void focus(void (*const func)(const coel::window::Focus &));
                void defocus(void (*const func)(const coel::window::Defocus &));
            } // namespace window
        }}    // namespace callback::set
        namespace create {
            Window agnostic(const int width, const int height, const char *title);
            Window vulkan(const int width, const int height, const char *title);
            Window direct3d(const int width, const int height, const char *title);
            Window opengl(const int width, const int height, const char *title);
        } // namespace create
        namespace update {
            bool agnostic(const Window *window);
            bool vulkan(const Window *window);
            bool direct3d(const Window *window);
            bool opengl(const Window *window);
        } // namespace update
        void set_cursor_pos(const Window *window, const float x, const float y);
        void set_cursor_visibility(const Window *window, const bool value);
        double get_time();
    } // namespace agnostic

    //
    //
    //
    //
    //
    namespace glfw {
        namespace callback { namespace set {
            namespace mouse {
                void press(void (*const func)(const coel::mouse::Press &));
                void release(void (*const func)(const coel::mouse::Release &));
                void scroll(void (*const func)(const coel::mouse::Scroll &));
                void move(void (*const func)(const coel::mouse::Move &));
            } // namespace mouse
            namespace key {
                void press(void (*const func)(const coel::key::Press &));
                void repeat(void (*const func)(const coel::key::Repeat &));
                void release(void (*const func)(const coel::key::Release &));
            } // namespace key
            namespace window {
                void move(void (*const func)(const coel::window::Move &));
                void resize(void (*const func)(const coel::window::Resize &));
                void close(void (*const func)(const coel::window::Close &));
                void focus(void (*const func)(const coel::window::Focus &));
                void defocus(void (*const func)(const coel::window::Defocus &));
            } // namespace window
        }}    // namespace callback::set
        namespace create {
            Window agnostic(const int width, const int height, const char *title);
            Window vulkan(const int width, const int height, const char *title);
            Window direct3d(const int width, const int height, const char *title);
            Window opengl(const int width, const int height, const char *title);
        } // namespace create
        namespace update {
            bool agnostic(const Window *window);
            bool vulkan(const Window *window);
            bool direct3d(const Window *window);
            bool opengl(const Window *window);
        } // namespace update
        void set_cursor_pos(const Window *window, const float x, const float y);
        void set_cursor_visibility(const Window *window, const bool value);
        double get_time();
    } // namespace glfw

    //
    //
    //
    //
    //
    namespace win32 {
        namespace callback { namespace set {
            namespace mouse {
                void press(void (*const func)(const coel::mouse::Press &));
                void release(void (*const func)(const coel::mouse::Release &));
                void scroll(void (*const func)(const coel::mouse::Scroll &));
                void move(void (*const func)(const coel::mouse::Move &));
            } // namespace mouse
            namespace key {
                void press(void (*const func)(const coel::key::Press &));
                void repeat(void (*const func)(const coel::key::Repeat &));
                void release(void (*const func)(const coel::key::Release &));
            } // namespace key
            namespace window {
                void move(void (*const func)(const coel::window::Move &));
                void resize(void (*const func)(const coel::window::Resize &));
                void close(void (*const func)(const coel::window::Close &));
                void focus(void (*const func)(const coel::window::Focus &));
                void defocus(void (*const func)(const coel::window::Defocus &));
            } // namespace window
        }}    // namespace callback::set
        namespace create {
            Window agnostic(const int width, const int height, const char *title);
            Window vulkan(const int width, const int height, const char *title);
            Window direct3d(const int width, const int height, const char *title);
            Window opengl(const int width, const int height, const char *title);
        } // namespace create
        namespace update {
            bool agnostic(const Window *window);
            bool vulkan(const Window *window);
            bool direct3d(const Window *window);
            bool opengl(const Window *window);
        } // namespace update
        void set_cursor_pos(const Window *window, const float x, const float y);
        void set_cursor_visibility(const Window *window, const bool value);
        double get_time();
    } // namespace win32
}}}   // namespace coel::window::_internal

//
//
//
//
//

//
//
//
//
//

namespace coel { namespace window {
    namespace callback { namespace set {
        namespace mouse {
            template <WindowAPI W = WindowAPI::_COEL_DEFAULT_WINDOW_API>
            void move(void (*const func)(const coel::mouse::Move &)) {
                switch (W) {
                case WindowAPI::Agnostic: _internal::agnostic::callback::set::mouse::move(func); return;
                case WindowAPI::Win32: _internal::win32::callback::set::mouse::move(func); return;
                case WindowAPI::GLFW: _internal::glfw::callback::set::mouse::move(func); return;
                default: return;
                }
            }
            template <WindowAPI W = WindowAPI::_COEL_DEFAULT_WINDOW_API>
            void scroll(void (*const func)(const coel::mouse::Scroll &)) {
                switch (W) {
                case WindowAPI::Agnostic: _internal::agnostic::callback::set::mouse::scroll(func); return;
                case WindowAPI::Win32: _internal::win32::callback::set::mouse::scroll(func); return;
                case WindowAPI::GLFW: _internal::glfw::callback::set::mouse::scroll(func); return;
                default: return;
                }
            }
            template <WindowAPI W = WindowAPI::_COEL_DEFAULT_WINDOW_API>
            void press(void (*const func)(const coel::mouse::Press &)) {
                switch (W) {
                case WindowAPI::Agnostic: _internal::agnostic::callback::set::mouse::press(func); return;
                case WindowAPI::Win32: _internal::win32::callback::set::mouse::press(func); return;
                case WindowAPI::GLFW: _internal::glfw::callback::set::mouse::press(func); return;
                default: return;
                }
            }
            template <WindowAPI W = WindowAPI::_COEL_DEFAULT_WINDOW_API>
            void release(void (*const func)(const coel::mouse::Release &)) {
                switch (W) {
                case WindowAPI::Agnostic: _internal::agnostic::callback::set::mouse::release(func); return;
                case WindowAPI::Win32: _internal::win32::callback::set::mouse::release(func); return;
                case WindowAPI::GLFW: _internal::glfw::callback::set::mouse::release(func); return;
                default: return;
                }
            }
        } // namespace mouse

        //
        //
        //
        //
        //

        namespace key {
            template <WindowAPI W = WindowAPI::_COEL_DEFAULT_WINDOW_API>
            void press(void (*const func)(const coel::key::Press &)) {
                switch (W) {
                case WindowAPI::Agnostic: _internal::agnostic::callback::set::key::press(func); return;
                case WindowAPI::Win32: _internal::win32::callback::set::key::press(func); return;
                case WindowAPI::GLFW: _internal::glfw::callback::set::key::press(func); return;
                default: return;
                }
            }
            template <WindowAPI W = WindowAPI::_COEL_DEFAULT_WINDOW_API>
            void repeat(void (*const func)(const coel::key::Repeat &)) {
                switch (W) {
                case WindowAPI::Agnostic: _internal::agnostic::callback::set::key::repeat(func); return;
                case WindowAPI::Win32: _internal::win32::callback::set::key::repeat(func); return;
                case WindowAPI::GLFW: _internal::glfw::callback::set::key::repeat(func); return;
                default: return;
                }
            }
            template <WindowAPI W = WindowAPI::_COEL_DEFAULT_WINDOW_API>
            void release(void (*const func)(const coel::key::Release &)) {
                switch (W) {
                case WindowAPI::Agnostic: _internal::agnostic::callback::set::key::release(func); return;
                case WindowAPI::Win32: _internal::win32::callback::set::key::release(func); return;
                case WindowAPI::GLFW: _internal::glfw::callback::set::key::release(func); return;
                default: return;
                }
            }
        } // namespace key

        //
        //
        //
        //
        //

        namespace window {
            template <WindowAPI W = WindowAPI::_COEL_DEFAULT_WINDOW_API>
            void move(void (*const func)(const coel::window::Move &)) {
                switch (W) {
                case WindowAPI::Agnostic: _internal::agnostic::callback::set::window::move(func); return;
                case WindowAPI::Win32: _internal::win32::callback::set::window::move(func); return;
                case WindowAPI::GLFW: _internal::glfw::callback::set::window::move(func); return;
                default: return;
                }
            }
            template <WindowAPI W = WindowAPI::_COEL_DEFAULT_WINDOW_API>
            void resize(void (*const func)(const coel::window::Resize &)) {
                switch (W) {
                case WindowAPI::Agnostic: _internal::agnostic::callback::set::window::resize(func); return;
                case WindowAPI::Win32: _internal::win32::callback::set::window::resize(func); return;
                case WindowAPI::GLFW: _internal::glfw::callback::set::window::resize(func); return;
                default: return;
                }
            }
            template <WindowAPI W = WindowAPI::_COEL_DEFAULT_WINDOW_API>
            void close(void (*const func)(const coel::window::Close &)) {
                switch (W) {
                case WindowAPI::Agnostic: _internal::agnostic::callback::set::window::close(func); return;
                case WindowAPI::Win32: _internal::win32::callback::set::window::close(func); return;
                case WindowAPI::GLFW: _internal::glfw::callback::set::window::close(func); return;
                default: return;
                }
            }
            template <WindowAPI W = WindowAPI::_COEL_DEFAULT_WINDOW_API>
            void focus(void (*const func)(const coel::window::Focus &)) {
                switch (W) {
                case WindowAPI::Agnostic: _internal::agnostic::callback::set::window::focus(func); return;
                case WindowAPI::Win32: _internal::win32::callback::set::window::focus(func); return;
                case WindowAPI::GLFW: _internal::glfw::callback::set::window::focus(func); return;
                default: return;
                }
            }
            template <WindowAPI W = WindowAPI::_COEL_DEFAULT_WINDOW_API>
            void defocus(void (*const func)(const coel::window::Defocus &)) {
                switch (W) {
                case WindowAPI::Agnostic: _internal::agnostic::callback::set::window::defocus(func); return;
                case WindowAPI::Win32: _internal::win32::callback::set::window::defocus(func); return;
                case WindowAPI::GLFW: _internal::glfw::callback::set::window::defocus(func); return;
                default: return;
                }
            }
        } // namespace window
    }}    // namespace callback::set

    //
    //
    //
    //
    //

    template <WindowAPI W = WindowAPI::_COEL_DEFAULT_WINDOW_API, RendererAPI R = RendererAPI::_COEL_DEFAULT_RENDERER_API>
    Window create(const int width, const int height, const char *title) {
        switch (W) {
        case WindowAPI::Agnostic:
            switch (R) {
            case RendererAPI::Agnostic: return _internal::agnostic::create::agnostic(width, height, title);
            case RendererAPI::Vulkan: return _internal::agnostic::create::vulkan(width, height, title);
            case RendererAPI::Direct3D: return _internal::agnostic::create::direct3d(width, height, title);
            case RendererAPI::OpenGL: return _internal::agnostic::create::opengl(width, height, title);
            default: return {WindowAPI::Agnostic, RendererAPI::None, nullptr, width, height};
            }
        case WindowAPI::Win32:
            switch (R) {
            case RendererAPI::Agnostic: return _internal::win32::create::agnostic(width, height, title);
            case RendererAPI::Vulkan: return _internal::win32::create::vulkan(width, height, title);
            case RendererAPI::Direct3D: return _internal::win32::create::direct3d(width, height, title);
            case RendererAPI::OpenGL: return _internal::win32::create::opengl(width, height, title);
            default: return {WindowAPI::Win32, RendererAPI::None, nullptr, width, height};
            }
        case WindowAPI::GLFW:
            switch (R) {
            case RendererAPI::Agnostic: return _internal::glfw::create::agnostic(width, height, title);
            case RendererAPI::Vulkan: return _internal::glfw::create::vulkan(width, height, title);
            case RendererAPI::Direct3D: return _internal::glfw::create::direct3d(width, height, title);
            case RendererAPI::OpenGL: return _internal::glfw::create::opengl(width, height, title);
            default: return {WindowAPI::GLFW, RendererAPI::None, nullptr, width, height};
            }
        default:
            switch (R) {
            case RendererAPI::Agnostic: return {WindowAPI::None, RendererAPI::Agnostic, 0, width, height};
            case RendererAPI::Vulkan: return {WindowAPI::None, RendererAPI::Vulkan, 0, width, height};
            case RendererAPI::Direct3D: return {WindowAPI::None, RendererAPI::Direct3D, 0, width, height};
            case RendererAPI::OpenGL: return {WindowAPI::None, RendererAPI::OpenGL, 0, width, height};
            default: return {WindowAPI::None, RendererAPI::None, nullptr, width, height};
            }
        }
    }

    //
    //
    //
    //
    //

    template <WindowAPI W = WindowAPI::_COEL_DEFAULT_WINDOW_API, RendererAPI R = RendererAPI::_COEL_DEFAULT_RENDERER_API>
    bool update(const Window *window) {
        switch (W) {
        case WindowAPI::Agnostic:
            switch (R) {
            case RendererAPI::Agnostic: return _internal::agnostic::update::agnostic(window);
            case RendererAPI::Vulkan: return _internal::agnostic::update::vulkan(window);
            case RendererAPI::Direct3D: return _internal::agnostic::update::direct3d(window);
            case RendererAPI::OpenGL: return _internal::agnostic::update::opengl(window);
            default: return false;
            }
        case WindowAPI::Win32:
            switch (R) {
            case RendererAPI::Agnostic: return _internal::win32::update::agnostic(window);
            case RendererAPI::Vulkan: return _internal::win32::update::vulkan(window);
            case RendererAPI::Direct3D: return _internal::win32::update::direct3d(window);
            case RendererAPI::OpenGL: return _internal::win32::update::opengl(window);
            default: return false;
            }
        case WindowAPI::GLFW:
            switch (R) {
            case RendererAPI::Agnostic: return _internal::glfw::update::agnostic(window);
            case RendererAPI::Vulkan: return _internal::glfw::update::vulkan(window);
            case RendererAPI::Direct3D: return _internal::glfw::update::direct3d(window);
            case RendererAPI::OpenGL: return _internal::glfw::update::opengl(window);
            default: return false;
            }
        default: return false;
        }
    }

    //
    //
    //
    //
    //

    template <WindowAPI W = WindowAPI::_COEL_DEFAULT_WINDOW_API>
    void set_cursor_pos(const Window *window, const float x, const float y) {
        switch (W) {
        case WindowAPI::Agnostic: _internal::agnostic::set_cursor_pos(window, x, y); return;
        case WindowAPI::Win32: _internal::win32::set_cursor_pos(window, x, y); return;
        case WindowAPI::GLFW: _internal::glfw::set_cursor_pos(window, x, y); return;
        default: return;
        }
    }

    //
    //
    //
    //
    //

    template <WindowAPI W = WindowAPI::_COEL_DEFAULT_WINDOW_API>
    void set_cursor_visibility(const Window *window, const bool value) {
        switch (W) {
        case WindowAPI::Agnostic: _internal::agnostic::set_cursor_visibility(window, value); return;
        case WindowAPI::Win32: _internal::win32::set_cursor_visibility(window, value); return;
        case WindowAPI::GLFW: _internal::glfw::set_cursor_visibility(window, value); return;
        default: return;
        }
    }

    //
    //
    //
    //
    //

    template <WindowAPI W = WindowAPI::_COEL_DEFAULT_WINDOW_API> double get_time() {
        switch (W) {
        case WindowAPI::Agnostic: return _internal::agnostic::get_time();
        case WindowAPI::Win32: return _internal::win32::get_time();
        case WindowAPI::GLFW: return _internal::glfw::get_time();
        default: return 0.0;
        }
    }
}} // namespace coel::window
