#include <glad/glad.h>

namespace Coel { namespace Renderer { namespace Command {
    void clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //
    }
    void setClearColor(float r, float g, float b, float a) {
        glClearColor(r, g, b, a); //
    }
    void resizeViewport(int x, int y, int w, int h) { 
        glViewport(x, y, w, h); //
    }
}}} // namespace Coel::Renderer::Command
