#include "../coel.hpp"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace coel {
    Window::Window(const unsigned int width, const unsigned int height, const char *const title)
        : width(width), height(height), title(title) {
        init(width, height, title);
    }
    void Window::init(const unsigned int width, const unsigned int height, const char *const title) {
        this->width = width, this->height = height, this->title = title;
        // init window manager
        glfwInit();
        GLFWwindow *result = glfwCreateWindow(width, height, title, nullptr, nullptr);
        window_handle = reinterpret_cast<void *>(result);
        glfwMakeContextCurrent(result);
        // window manager prop
        glfwSwapInterval(true);
        glfwSetWindowUserPointer(result, this);
        // set window callbacks
        glfwSetKeyCallback(result, [](GLFWwindow *w, int key, int scancode, int action, int mods) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            switch (action) {
            case GLFW_PRESS: window->key_press({key, scancode, mods}); break;
            case GLFW_REPEAT: window->key_repeat({key, scancode, mods}); break;
            case GLFW_RELEASE: window->key_release({key, scancode, mods}); break;
            }
        });
        glfwSetMouseButtonCallback(result, [](GLFWwindow *w, int button, int action, int mods) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            switch (action) {
            case GLFW_PRESS: window->mouse_press({button, mods}); break;
            case GLFW_RELEASE: window->mouse_release({button, mods}); break;
            }
        });
        glfwSetCursorPosCallback(result, [](GLFWwindow *w, double xPos, double yPos) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            window->mouse = {float(xPos), float(yPos)};
            window->mouse_move({xPos, yPos});
        });
        glfwSetScrollCallback(result, [](GLFWwindow *w, double xOffset, double yOffset) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            window->mouse_scroll({xOffset, yOffset});
        });
        glfwSetWindowPosCallback(result, [](GLFWwindow *w, int xPos, int yPos) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            window->window_move({xPos, yPos});
        });
        glfwSetWindowSizeCallback(result, [](GLFWwindow *w, int width, int height) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            renderer::viewport(width, height);
            renderer::batch2d::resize(width, height);
            window->width = width, window->height = height;
            window->window_resize({width, height});
        });
        glfwSetWindowFocusCallback(result, [](GLFWwindow *w, int focus) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            switch (focus) {
            case GLFW_TRUE: window->window_focus({}); return;
            case GLFW_FALSE: window->window_defocus({}); return;
            }
        });
        glfwSetWindowCloseCallback(result, [](GLFWwindow *w) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            window->window_close({});
        });

        // init opengl context
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        // opengl prop
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    void Window::update() {
        GLFWwindow *window = reinterpret_cast<GLFWwindow *>(window_handle);
        glfwPollEvents();
        this->on_update();
        glfwSwapBuffers(window);
        renderer::clear();
    }
    void Window::make_current() { glfwMakeContextCurrent(reinterpret_cast<GLFWwindow *>(window_handle)); }
    bool Window::should_close() { return glfwWindowShouldClose(reinterpret_cast<GLFWwindow *>(window_handle)); }
    float Window::get_time() { return glfwGetTime(); }
} // namespace coel
