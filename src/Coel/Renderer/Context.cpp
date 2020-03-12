#include <iostream>

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Coel { namespace Renderer { namespace Context {
    int init(void *const windowHandle) {
        glfwMakeContextCurrent((GLFWwindow *)windowHandle);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to bind OpenGL Context\n";
            glfwTerminate();
            return -1;
        }

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        return 0;
    }
}}} // namespace Coel::Renderer::Context
