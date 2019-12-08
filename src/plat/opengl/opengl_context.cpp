#include "common.hpp"
#include <coel/renderer/context.hpp>
#define GLFW_INCLUDE_NONE 1
#include <GLFW/glfw3.h>

#include <debug/debug.hpp>

namespace coel { namespace opengl {
    Context::Context(GLFWwindow *window) : m_window(window) {
        DEBUG_BEGIN_FUNC_PROFILE;

        glfwMakeContextCurrent(m_window);
        gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));
    }

    void Context::swap() {
        DEBUG_BEGIN_FUNC_PROFILE;

        glfwSwapBuffers(m_window);
    }

    void Context::bind() {
        DEBUG_BEGIN_FUNC_PROFILE;

        glfwMakeContextCurrent(m_window);
    }
}} // namespace coel::opengl
