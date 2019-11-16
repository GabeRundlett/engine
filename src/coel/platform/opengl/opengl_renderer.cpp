#include "common.hpp"
#include <core/renderer.hpp>

#include <debug.hpp>

namespace coel { namespace opengl {
    void init() {
        SCOPED_PROFILE;

        GL_CALL(glEnable(GL_BLEND));
        GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    }
    void clear() {
        SCOPED_PROFILE;

        GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }
    void set_clear_color(float r, float g, float b, float a) {
        SCOPED_PROFILE;

        GL_CALL(glClearColor(r, g, b, a));
    }
    void set_viewport(float x, float y, float width, float height) {
        SCOPED_PROFILE;

        GL_CALL(glViewport(x, y, width, height));
    }
}} // namespace coel::opengl
