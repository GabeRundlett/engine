#pragma once

namespace coel { namespace mouse {
    struct Press {
        int button, mods;
    };
    struct Release {
        int button, mods;
    };
    struct Scroll {
        double x, y;
    };
    struct Move {
        double x, y;
    };
}} // namespace coel::mouse

namespace coel { namespace key {
    struct Press {
        int key, scancode, mods;
    };
    struct Repeat {
        int key, scancode, mods;
    };
    struct Release {
        int key, scancode, mods;
    };
}} // namespace coel::key

namespace coel { namespace window {
    struct Move {
        int x, y;
    };
    struct Resize {
        int width, height;
    };
    struct Close {};
    struct Focus {};
    struct Defocus {};
}} // namespace coel::window
