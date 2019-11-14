#pragma once

#include "events.hpp"
#include "window.hpp"

namespace coel {
    class App {
      protected:
        Ref<Window> m_window;

      public:
        App() { m_window = create_window(800, 800, "Application Window"); }

        virtual void update() {}
        void run() {
            while (m_window->is_open()) {
                update();
                m_window->update();
            }
        }
    };

    extern Scope<App> create_app();
} // namespace coel

int main() {
    auto app = coel::create_app();
    app->run();
    return 0;
}
