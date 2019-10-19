#include "../../coel.hpp"
#include <glad/glad.h>

namespace coel { namespace renderer {
    void clear() { glClear(GL_COLOR_BUFFER_BIT); }
    void clear_color(const math::Color &color) {
        constexpr float fac = 1.f / 255;
        glClearColor(fac * color.r, fac * color.g, fac * color.b, fac * color.a);
    }
    void clear_color(const float r, const float g, const float b, const float a) { glClearColor(r, g, b, a); }
    void viewport(const float width, const float height) { glViewport(0, 0, width, height); }
}} // namespace coel::renderer
