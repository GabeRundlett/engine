#pragma once

#include <Coel/Model.hpp>

namespace Coel { namespace Renderer {
    void clear();
    void clearColor();
    void clearDepth();
    void setClearColor(float r, float g, float b, float a);
    void resizeViewport(int32_t l, int32_t t, int32_t r, int32_t b);
    void enableBlend(bool mode);
    void enableCulling(bool mode);
    void enableDepthTest(bool mode);
    void enableWireframe(bool mode);
    void draw(const Model &model);
    void draw(const Vao &vao, uint32_t count);
    void drawIndexed(const Vao &vao, uint32_t count);
}} // namespace Coel::Renderer
