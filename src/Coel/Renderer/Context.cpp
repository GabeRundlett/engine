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

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        return 0;
    }
}}} // namespace Coel::Renderer::Context
 