#include <iostream>

#include "Window.hpp"
#include "Renderer/Context.hpp"
#include "Renderer/Renderer.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Coel {
    static GLFWwindow *windowHandle;
    void dwc(Window &w) {} // default window callback

    Window::Window(int width, int height, const char *const title)
        : size{width, height}, mouse{{0, 0}, 0, 0, 0}, onResize(dwc), onMouseScroll(dwc), onMouseMove(dwc), onMouseButton(dwc),
          onKey(dwc) {
        init(width, height, title); //
    }

    Window::~Window() {
        deinit(); //
    }

    int Window::init(int width, int height, const char *const title) {
        if (!glfwInit()) {
            std::cerr << "Failed to initalize GLFW\n";
            return -1;
        }

        windowHandle = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!windowHandle) {
            std::cerr << "Failed to create window\n";
            deinit();
            return -1;
        }
        if (Renderer::Context::init(windowHandle)) {
            std::cerr << "Failed to create valid render context\n";
            deinit();
            return -1;
        }

        glfwSetWindowUserPointer(windowHandle, this);
        glfwSetInputMode(windowHandle, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        // glfwSwapInterval(0);

        glfwSetWindowSizeCallback(windowHandle, [](GLFWwindow *glfwWindow, int w, int h) {
            Renderer::resizeViewport(0, 0, w, h);
            Window *window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
            window->size = {w, h};
            window->onResize(*window);
        });

        glfwSetCursorPosCallback(windowHandle, [](GLFWwindow *glfwWindow, double x, double y) {
            Window *window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
            window->mouse.pos = {x, y};
            window->onMouseMove(*window);
        });
        glfwSetScrollCallback(windowHandle, [](GLFWwindow *glfwWindow, double x, double y) {
            Window *window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
            window->mouse.scrollOffset = {x, y};
            window->onMouseScroll(*window);
        });
        glfwSetMouseButtonCallback(windowHandle, [](GLFWwindow *glfwWindow, int button, int action, int mods) {
            Window *window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
            window->mouse.button = button;
            window->mouse.action = action;
            window->mouse.mods = mods;
            window->onMouseButton(*window);
        });

        glfwSetKeyCallback(windowHandle, [](GLFWwindow *glfwWindow, int key, int scancode, int action, int mods) {
            Window *window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
            window->key.code = key;
            window->key.action = action;
            window->key.mods = mods;
            window->onKey(*window);
        });

        return 0;
    }

    void Window::update() {
        glfwPollEvents();
        glfwSwapBuffers(windowHandle);
    }

    bool Window::isOpen() const {
        return !glfwWindowShouldClose(windowHandle); //
    }

    double Window::getTime() const {
        return glfwGetTime(); //
    }

    void Window::cursorTo(const Math::Vec2d &pos) {
        mouse.pos = pos;
        glfwSetCursorPos(windowHandle, pos.x, pos.y);
    }

    void Window::cursorMode(const unsigned int mode) {
        glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL + mode); //
    }

    void Window::deinit() {
        glfwTerminate(); //
    }
    void Window::close() {
        glfwSetWindowShouldClose(windowHandle, true); //
    }
    void Window::resize() {
        Renderer::resizeViewport(0, 0, size.x, size.y);
        onResize(*this);
    }
    GLFWwindow *Window::getGlfwWindow() { return windowHandle; }
} // namespace Coel
