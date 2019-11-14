#pragma once

#include "events.hpp"
#include "window.hpp"

namespace coel {
    class App {
      protected:
        Ref<Window> m_window;
    };

    extern Scope<App> create_app();
} // namespace coel

int main() {
    auto app = coel::create_app();
    app->run();
    return 0;
}
