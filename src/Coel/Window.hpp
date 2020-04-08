#pragma once

#include <glm/glm.hpp>
#include "Input.hpp"

#include <memory>
#include <functional>

struct GLFWwindow;

namespace Coel {
    enum CursorMode {
        Normal,
        Hidden,
        Disabled,
    };

    struct Window {
        bool isOpen{true};
        glm::ivec2 size{800, 600};
        const char *const title{"Coel Window"};
        KeyInfo key{};
        MouseInfo mouse{};
        GLFWwindow *glfwHandle{};
        std::function<void(Window &)> onResize{}, onMouseButton{}, onMouseMove{}, onMouseScroll{}, onKey{}, onChar{};
        Window(const glm::ivec2 size, const char *const title) : size(size), title{title} {}
        Window(const char *const title) : title{title} {}
        Window() = default;
    };

    int create(Window &window);
    void destroy(Window &window);
    void update(Window &window);
    double getTime();
} // namespace Coel
