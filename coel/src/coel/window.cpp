#include "window.hpp"
#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace coel { namespace window { namespace _internal {
    namespace agnostic {

        //
        //
        //
        //
        //

        namespace callback { namespace set {
            namespace mouse {
                void press(void (*const func)(const coel::mouse::Press &)) {}
                void release(void (*const func)(const coel::mouse::Release &)) {}
                void scroll(void (*const func)(const coel::mouse::Scroll &)) {}
                void move(void (*const func)(const coel::mouse::Move &)) {}
            } // namespace mouse

            namespace key {
                void press(void (*const func)(const coel::key::Press &)) {}
                void repeat(void (*const func)(const coel::key::Repeat &)) {}
                void release(void (*const func)(const coel::key::Release &)) {}
            } // namespace key

            namespace window {
                void move(void (*const func)(const coel::window::Move &)) {}
                void resize(void (*const func)(const coel::window::Resize &)) {}
                void close(void (*const func)(const coel::window::Close &)) {}
                void focus(void (*const func)(const coel::window::Focus &)) {}
                void defocus(void (*const func)(const coel::window::Defocus &)) {}
            } // namespace window
        }}    // namespace callback::set

        //
        //
        //
        //
        //

        namespace create {
            Window agnostic(const int width, const int height, const char *title) {
                return {WindowAPI::Agnostic, RendererAPI::Agnostic, nullptr, width, height};
            }
            Window vulkan(const int width, const int height, const char *title) {
                return {WindowAPI::Agnostic, RendererAPI::Vulkan, nullptr, width, height};
            }
            Window direct3d(const int width, const int height, const char *title) {
                return {WindowAPI::Agnostic, RendererAPI::Direct3D, nullptr, width, height};
            }
            Window opengl(const int width, const int height, const char *title) {
                return {WindowAPI::Agnostic, RendererAPI::OpenGL, nullptr, width, height};
            }
        } // namespace create

        //
        //
        //
        //
        //

        namespace update {
            bool agnostic(const Window *window) { return false; }
            bool vulkan(const Window *window) { return false; }
            bool direct3d(const Window *window) { return false; }
            bool opengl(const Window *window) { return false; }
        } // namespace update

        //
        //
        //
        //
        //

        void set_cursor_pos(const Window *window, const float x, const float y) {}

        //
        //
        //
        //
        //

        void set_cursor_visibility(const Window *window, const bool value) {}

        //
        //
        //
        //
        //

        double get_time() { return 0.0; }
    } // namespace agnostic

    //
    //
    //
    //
    //

    namespace glfw {

        //
        //
        //
        //
        //

        static void empty_mouse_press_callback(const coel::mouse::Press &) {}
        static void (*s_mouse_press_callback)(const coel::mouse::Press &) = empty_mouse_press_callback;
        static void empty_mouse_release_callback(const coel::mouse::Release &) {}
        static void (*s_mouse_release_callback)(const coel::mouse::Release &) = empty_mouse_release_callback;
        static void empty_mouse_scroll_callback(const coel::mouse::Scroll &) {}
        static void (*s_mouse_scroll_callback)(const coel::mouse::Scroll &) = empty_mouse_scroll_callback;
        static void empty_mouse_move_callback(const coel::mouse::Move &) {}
        static void (*s_mouse_move_callback)(const coel::mouse::Move &) = empty_mouse_move_callback;
        static void empty_key_press_callback(const coel::key::Press &) {}
        static void (*s_key_press_callback)(const coel::key::Press &) = empty_key_press_callback;
        static void empty_key_repeat_callback(const coel::key::Repeat &) {}
        static void (*s_key_repeat_callback)(const coel::key::Repeat &) = empty_key_repeat_callback;
        static void empty_key_release_callback(const coel::key::Release &) {}
        static void (*s_key_release_callback)(const coel::key::Release &) = empty_key_release_callback;
        static void empty_window_move_callback(const coel::window::Move &) {}
        static void (*s_window_move_callback)(const coel::window::Move &) = empty_window_move_callback;
        static void empty_window_resize_callback(const coel::window::Resize &) {}
        static void (*s_window_resize_callback)(const coel::window::Resize &) = empty_window_resize_callback;
        static void empty_window_close_callback(const coel::window::Close &) {}
        static void (*s_window_close_callback)(const coel::window::Close &) = empty_window_close_callback;
        static void empty_window_focus_callback(const coel::window::Focus &) {}
        static void (*s_window_focus_callback)(const coel::window::Focus &) = empty_window_focus_callback;
        static void empty_window_defocus_callback(const coel::window::Defocus &) {}
        static void (*s_window_defocus_callback)(const coel::window::Defocus &) = empty_window_defocus_callback;
        namespace callback { namespace set {
            namespace mouse {
            } // namespace mouse
            namespace mouse {
                void press(void (*const func)(const coel::mouse::Press &)) { s_mouse_press_callback = func; }
                void release(void (*const func)(const coel::mouse::Release &)) { s_mouse_release_callback = func; }
                void scroll(void (*const func)(const coel::mouse::Scroll &)) { s_mouse_scroll_callback = func; }
                void move(void (*const func)(const coel::mouse::Move &)) { s_mouse_move_callback = func; }
            } // namespace mouse
            namespace key {
                void press(void (*const func)(const coel::key::Press &)) { s_key_press_callback = func; }
                void repeat(void (*const func)(const coel::key::Repeat &)) { s_key_repeat_callback = func; }
                void release(void (*const func)(const coel::key::Release &)) { s_key_release_callback = func; }
            } // namespace key
            namespace window {
                void move(void (*const func)(const coel::window::Move &)) { s_window_move_callback = func; }
                void resize(void (*const func)(const coel::window::Resize &)) { s_window_resize_callback = func; }
                void close(void (*const func)(const coel::window::Close &)) { s_window_close_callback = func; }
                void focus(void (*const func)(const coel::window::Focus &)) { s_window_focus_callback = func; }
                void defocus(void (*const func)(const coel::window::Defocus &)) { s_window_defocus_callback = func; }
            } // namespace window
        }}    // namespace callback::set

        //
        //
        //
        //
        //

        namespace create {
            Window agnostic(const int width, const int height, const char *title) {
                return {WindowAPI::GLFW, RendererAPI::Agnostic, nullptr, width, height};
            }
            Window vulkan(const int width, const int height, const char *title) {
                return {WindowAPI::GLFW, RendererAPI::Vulkan, nullptr, width, height};
            }
            Window direct3d(const int width, const int height, const char *title) {
                return {WindowAPI::GLFW, RendererAPI::Direct3D, nullptr, width, height};
            }
            Window opengl(const int width, const int height, const char *title) {
                glfwInit();
                GLFWwindow *result = glfwCreateWindow(width, height, title, nullptr, nullptr);
                glfwMakeContextCurrent(result);
                glfwSwapInterval(false);

                // init opengl context
                gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                // set callbacks
                glfwSetKeyCallback(result, [](GLFWwindow *w, int key, int scancode, int action, int mods) {
                    switch (action) {
                    case GLFW_PRESS: s_key_press_callback({key, scancode, mods}); break;
                    case GLFW_REPEAT: s_key_repeat_callback({key, scancode, mods}); break;
                    case GLFW_RELEASE: s_key_release_callback({key, scancode, mods}); break;
                    }
                });
                glfwSetMouseButtonCallback(result, [](GLFWwindow *w, int button, int action, int mods) {
                    switch (action) {
                    case GLFW_PRESS: s_mouse_press_callback({button, mods}); break;
                    case GLFW_RELEASE: s_mouse_release_callback({button, mods}); break;
                    }
                });
                glfwSetCursorPosCallback(result, [](GLFWwindow *w, double xPos, double yPos) {
                    s_mouse_move_callback({xPos, yPos});
                });
                glfwSetScrollCallback(result, [](GLFWwindow *w, double xOffset, double yOffset) {
                    s_mouse_scroll_callback({xOffset, yOffset});
                });

                glfwSetWindowPosCallback(result, [](GLFWwindow *w, int xPos, int yPos) {
                    s_window_move_callback({xPos, yPos});
                });
                glfwSetWindowSizeCallback(result, [](GLFWwindow *w, int width, int height) {
                    renderer::resize_viewport<RendererAPI::OpenGL>(width, height);
                    s_window_resize_callback({width, height});
                });
                glfwSetWindowFocusCallback(result, [](GLFWwindow *w, int focus) {
                    switch (focus) {
                    case GLFW_TRUE: s_window_focus_callback({}); return;
                    case GLFW_FALSE: s_window_defocus_callback({}); return;
                    }
                });
                glfwSetWindowCloseCallback(result, [](GLFWwindow *w) { s_window_close_callback({}); });

                return {WindowAPI::GLFW, RendererAPI::OpenGL, reinterpret_cast<void *>(result), width, height};
            }
        } // namespace create

        //
        //
        //
        //
        //

        namespace update {
            bool agnostic(const Window *window) { return false; }
            bool vulkan(const Window *window) { return false; }
            bool direct3d(const Window *window) { return false; }
            bool opengl(const Window *window) {
                glfwPollEvents();
                glfwSwapBuffers(reinterpret_cast<GLFWwindow *>(window->handle));
                return !glfwWindowShouldClose(reinterpret_cast<GLFWwindow *>(window->handle));
            }
        } // namespace update

        //
        //
        //
        //
        //

        void set_cursor_pos(const Window *window, const float x, const float y) {
            glfwSetCursorPos(reinterpret_cast<GLFWwindow *>(window->handle), x, y);
        }

        //
        //
        //
        //
        //

        void set_cursor_visibility(const Window *window, const bool value) {
            glfwSetInputMode(reinterpret_cast<GLFWwindow *>(window->handle), GLFW_CURSOR, GLFW_CURSOR_HIDDEN - value);
        }

        //
        //
        //
        //
        //

        double get_time() { return glfwGetTime(); }
    } // namespace glfw

    //
    //
    //
    //
    //

    namespace win32 {

        //
        //
        //
        //
        //

        namespace callback { namespace set {
            namespace mouse {
                void press(void (*const func)(const coel::mouse::Press &)) {}
                void release(void (*const func)(const coel::mouse::Release &)) {}
                void scroll(void (*const func)(const coel::mouse::Scroll &)) {}
                void move(void (*const func)(const coel::mouse::Move &)) {}
            } // namespace mouse

            namespace key {
                void press(void (*const func)(const coel::key::Press &)) {}
                void repeat(void (*const func)(const coel::key::Repeat &)) {}
                void release(void (*const func)(const coel::key::Release &)) {}
            } // namespace key

            namespace window {
                void move(void (*const func)(const coel::window::Move &)) {}
                void resize(void (*const func)(const coel::window::Resize &)) {}
                void close(void (*const func)(const coel::window::Close &)) {}
                void focus(void (*const func)(const coel::window::Focus &)) {}
                void defocus(void (*const func)(const coel::window::Defocus &)) {}
            } // namespace window
        }}    // namespace callback::set

        //
        //
        //
        //
        //

        namespace create {
            Window agnostic(const int width, const int height, const char *title) {
                return {WindowAPI::Win32, RendererAPI::Agnostic, nullptr, width, height};
            }
            Window vulkan(const int width, const int height, const char *title) {
                return {WindowAPI::Win32, RendererAPI::Vulkan, nullptr, width, height};
            }
            Window direct3d(const int width, const int height, const char *title) {
                return {WindowAPI::Win32, RendererAPI::Direct3D, nullptr, width, height};
            }
            Window opengl(const int width, const int height, const char *title) {
                return {WindowAPI::Win32, RendererAPI::OpenGL, nullptr, width, height};
            }
        } // namespace create

        //
        //
        //
        //
        //

        namespace update {
            bool agnostic(const Window *window) { return false; }
            bool vulkan(const Window *window) { return false; }
            bool direct3d(const Window *window) { return false; }
            bool opengl(const Window *window) { return false; }
        } // namespace update

        //
        //
        //
        //
        //

        void set_cursor_pos(const Window *window, const float x, const float y) {}

        //
        //
        //
        //
        //

        void set_cursor_visibility(const Window *window, const bool value) {}

        //
        //
        //
        //
        //

        double get_time() { return 0.0; }
    } // namespace win32
}}}   // namespace coel::window::_internal
