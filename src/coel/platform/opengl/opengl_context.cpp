#include "../../core/renderer/context.hpp"
#include "common.hpp"
#define GLFW_INCLUDE_NONE 1
#include <GLFW/glfw3.h>

#include <debug.hpp>

namespace coel { namespace opengl {
    Context::Context(GLFWwindow *window) : m_window(window) {
        SCOPED_PROFILE;

        glfwMakeContextCurrent(m_window);
        gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));
    }

    void Context::swap() {
        SCOPED_PROFILE;

        glfwSwapBuffers(m_window);
    }

    void Context::bind() {
        SCOPED_PROFILE;

        glfwMakeContextCurrent(m_window);
    }
}} // namespace coel::opengl
