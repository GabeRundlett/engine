#include <glad/glad.h>
#include "Renderer.hpp"

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
    void resizeViewport(int32_t x, int32_t y, int32_t w, int32_t h) {
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
        glFrontFace(GL_CCW);
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

    void draw(const Model &model) {
        for (const auto &o : model.objects) {
            uint32_t slot = 0;
            for (const auto &tex : o.textures) {
                if (slot > 31) break;
                bind(tex, slot);
                ++slot;
            }
            drawIndexed(o.vao, o.indexCount);
        }
    }

    void draw(const Vao &vao, uint32_t count) {
        bind(vao);
        glDrawArrays(GL_TRIANGLES, 0, count);
    }

    void drawIndexed(const Vao &vao, uint32_t count) {
        bind(vao);
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }
}} // namespace Coel::Renderer
