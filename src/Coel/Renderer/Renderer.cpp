#include <glad/glad.h>

namespace Coel { namespace Renderer {
    void clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //
    }
    void clearColor() {
        glClear(GL_COLOR_BUFFER_BIT); //
    }
    void clearDepth() {
        glClear(GL_DEPTH_BUFFER_BIT); //
    }
    void setClearColor(float r, float g, float b, float a) {
        glClearColor(r, g, b, a); //
    }
    void resizeViewport(int x, int y, int w, int h) {
        glViewport(x, y, w, h); //
    }
    void enableBlend(bool mode) {
        if (mode)
            glEnable(GL_BLEND);
        else
            glDisable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    void enableCulling(bool mode) {
        if (mode)
            glEnable(GL_CULL_FACE);
        else
            glDisable(GL_CULL_FACE);
        glFrontFace(GL_CW);
        glCullFace(GL_BACK);
    }
    void enableDepthTest(bool mode) {
        if (mode)
            glEnable(GL_DEPTH_TEST);
        else
            glDisable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }
    void enableWireframe(bool mode) {
        if (mode)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}} // namespace Coel::Renderer
