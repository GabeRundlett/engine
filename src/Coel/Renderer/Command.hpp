#pragma once

namespace Coel { namespace Renderer { namespace Command {
    void clear();
    void setClearColor(float r, float g, float b, float a);
    void resizeViewport(int l, int t, int r, int b);
}}} // namespace Coel::Renderer::Command
