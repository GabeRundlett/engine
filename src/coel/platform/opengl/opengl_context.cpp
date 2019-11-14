#include "../../core/renderer/context.hpp"
#include "common.hpp"
#define GLFW_INCLUDE_NONE 1
#include <GLFW/glfw3.h>

namespace coel { namespace opengl {
    Context::Context(GLFWwindow *window) : m_window(window) {
        glfwMakeContextCurrent(m_window);
        gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));
    }

    void Context::swap() { glfwSwapBuffers(m_window); }
}} // namespace coel::opengl
