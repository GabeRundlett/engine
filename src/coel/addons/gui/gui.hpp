#pragma once

namespace coel { namespace gui {
    void init();
    void draw_rect(const float x, const float y, const float w, const float h);
    void draw_line(const float x1, const float y1, const float x2, const float y2);
    void draw_ellipse(const float x, const float y, const float r1, const float r2);
    void draw_text(const float x, const float y, const char *const text);
    void flush();
}} // namespace coel::gui
