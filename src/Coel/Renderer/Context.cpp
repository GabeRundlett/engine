#include "Context.hpp"

#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Coel { namespace Renderer { namespace Context {
    int init(const Window &window) {
        glfwMakeContextCurrent(window.glfwHandle);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to bind OpenGL Context\n";
            glfwTerminate();
            return -1;
        }
        return 0;
    }
}}} // namespace Coel::Renderer::Context
