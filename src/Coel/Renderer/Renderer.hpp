#pragma once

#include "Buffer.hpp"

namespace Coel { namespace Renderer {
    void clear();
    void clearColor();
    void clearDepth();
    void setClearColor(float r, float g, float b, float a);
    void resizeViewport(int l, int t, int r, int b);
    void enableBlend(bool mode);
    void enableCulling(bool mode);
    void enableDepthTest(bool mode);
    void enableWireframe(bool mode);
    void draw(const Vao &vao, unsigned int count);
    void drawIndexed(const Vao &vao, unsigned int count);
}} // namespace Coel::Renderer
