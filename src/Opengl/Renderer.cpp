#include "Common.hpp"
#include "../Renderer.hpp"

namespace Coel { namespace Opengl {
    void init() {
        // DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(glEnable(GL_BLEND));
        GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    }
    void clear() {
        // DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }
    void set_clear_color(float r, float g, float b, float a) {
        // DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(glClearColor(r, g, b, a));
    }
    void set_viewport(int x, int y, int width, int height) {
        // DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(glViewport(x, y, width, height));
    }
}} // namespace Coel::Opengl
