#include <iostream>

#include "Window.hpp"
#include "Renderer/Context.hpp"
#include "Renderer/Renderer.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Coel {
    static std::size_t s_windowCount = 0;

    int create(Window &window) {
        if (!s_windowCount) {
            if (!glfwInit()) {
                std::cerr << "Failed to initalize GLFW\n";
                return -1;
            }
        }

        ++s_windowCount;

        static constexpr auto dwc = [](Window &) {};
        if (window.onResize == nullptr) window.onResize = dwc;
        if (window.onMouseButton == nullptr) window.onMouseButton = dwc;
        if (window.onMouseMove == nullptr) window.onMouseMove = dwc;
        if (window.onMouseScroll == nullptr) window.onMouseScroll = dwc;
        if (window.onKey == nullptr) window.onKey = dwc;
        if (window.onChar == nullptr) window.onChar = dwc;

        window.glfwHandle = glfwCreateWindow(window.size.x, window.size.y, window.title, nullptr, nullptr);
        if (!window.glfwHandle) {
            std::cerr << "Failed to create window\n";
            destroy(window);
            return -1;
        }

        if (Renderer::Context::init(window)) {
            std::cerr << "Failed to create valid render context\n";
            destroy(window);
            return -1;
        }

        glfwSetWindowUserPointer(window.glfwHandle, &window);
        glfwSetInputMode(window.glfwHandle, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        glfwWindowHint(GLFW_SAMPLES, 4);

        glfwSetWindowSizeCallback(window.glfwHandle, [](GLFWwindow *glfwWindow, int w, int h) {
            Renderer::resizeViewport(0, 0, w, h);
            Window *window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
            window->size = {w, h};
            window->onResize(*window);
        });
        glfwSetMouseButtonCallback(window.glfwHandle, [](GLFWwindow *glfwWindow, int button, int action, int mods) {
            Window *window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
            window->mouse.button = button;
            window->mouse.action = action;
            window->mouse.mods = mods;
            window->onMouseButton(*window);
        });
        glfwSetCursorPosCallback(window.glfwHandle, [](GLFWwindow *glfwWindow, double x, double y) {
            Window *window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
            window->mouse.pos = {x, y};
            window->onMouseMove(*window);
        });
        glfwSetScrollCallback(window.glfwHandle, [](GLFWwindow *glfwWindow, double x, double y) {
            Window *window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
            window->mouse.scrollOffset = {x, y};
            window->onMouseScroll(*window);
        });
        glfwSetKeyCallback(window.glfwHandle, [](GLFWwindow *glfwWindow, int key, int scancode, int action, int mods) {
            Window *window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
            window->key.code = key;
            window->key.scancode = scancode;
            window->key.action = action;
            window->key.mods = mods;
            window->onKey(*window);
        });
        glfwSetCharCallback(window.glfwHandle, [](GLFWwindow *glfwWindow, unsigned int codepoint) {
            Window *window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
            window->key.character = codepoint;
            window->onChar(*window);
        });
        return 0;
    }

    void destroy(Window &window) {
        glfwDestroyWindow(window.glfwHandle);
        --s_windowCount;
        if (!s_windowCount) glfwTerminate();
    }

    void update(Window &window) {
        glfwPollEvents();
        glfwSwapBuffers(window.glfwHandle);
        window.isOpen = !glfwWindowShouldClose(window.glfwHandle);
    }

    double getTime() {
        return glfwGetTime(); //
    }

    void cursorTo(Window &window, const glm::dvec2 &pos) {
        window.mouse.pos = pos;
        glfwSetCursorPos(window.glfwHandle, pos.x, pos.y);
    }

    void cursorMode(const Window &window, const unsigned int mode) {
        glfwSetInputMode(window.glfwHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL + mode); //
    }

    void close(const Window &window) {
        glfwSetWindowShouldClose(window.glfwHandle, true); //
    }

    void resize(Window &window) {
        Renderer::resizeViewport(0, 0, window.size.x, window.size.y);
        window.onResize(window);
    }
} // namespace Coel
