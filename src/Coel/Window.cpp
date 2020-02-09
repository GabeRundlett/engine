#include <iostream>
#include <GLFW/glfw3.h>

#include "Window.hpp"
#include "Renderer/Context.hpp"
#include "Renderer/Command.hpp"

namespace Coel {
    static GLFWwindow *windowHandle;
    void dwc(Window &w) {} // default window callback

    Window::Window(int width, int height, const char *const title)
        : size{width, height}, mouse{{0, 0}, 0, 0, 0}, onResize(dwc), onMouseMove(dwc), onMouseButton(dwc), onKey(dwc) {
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

        if (!Renderer::Context::init(windowHandle)) {
            std::cerr << "Failed to create valid render context\n";
            deinit();
            return -1;
        }

        glfwSetWindowUserPointer(windowHandle, this);

        glfwSetWindowSizeCallback(windowHandle, [](GLFWwindow *glfwWindow, int w, int h) {
            Renderer::Command::resizeViewport(0, 0, w, h);
            Window *window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
            window->size = {w, h};
            window->onResize(*window);
        });

        glfwSetCursorPosCallback(windowHandle, [](GLFWwindow *glfwWindow, double x, double y) {
            Window *window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
            window->mouse.pos = {x, y};
            window->onMouseMove(*window);
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

    void Window::deinit() {
        glfwTerminate(); //
    }
} // namespace Coel
