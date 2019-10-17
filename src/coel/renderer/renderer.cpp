#include "../../coel.hpp"
#include <glad/glad.h>

namespace coel { namespace renderer {
    void clear(const unsigned int color) {
        const float fac = 1.f / 255;
        const float r = static_cast<const unsigned char>(color >> 24);
        const float g = static_cast<const unsigned char>(color >> 16);
        const float b = static_cast<const unsigned char>(color >> 8);
        const float a = static_cast<const unsigned char>(color);
        glClearColor(r * fac, g * fac, b * fac, a * fac);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    void clear(const float r, const float g, const float b, const float a) {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    void viewport(const float width, const float height) { glViewport(0, 0, width, height); }
}} // namespace coel::renderer
