#include "Common.hpp"
#include "Context.hpp"

#define GLFW_INCLUDE_NONE 1
#include <GLFW/glfw3.h>

namespace Coel { namespace Opengl {
    Context::Context(GLFWwindow *window) : mWindow(window) {
        // DEBUG_BEGIN_FUNC_PROFILE;

        glfwMakeContextCurrent(mWindow);
        gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));
    }

    void Context::swap() {
        // DEBUG_BEGIN_FUNC_PROFILE;

        glfwSwapBuffers(mWindow);
    }

    void Context::bind() {
        // DEBUG_BEGIN_FUNC_PROFILE;

        glfwMakeContextCurrent(mWindow);
    }
}} // namespace Coel::Opengl
