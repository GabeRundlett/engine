#include <Coel.hpp>

int main() {
    int res = 0;
    for (unsigned int i = 0; i < 5; ++i) {
        Coel::Window window;
        if (Coel::create(window)) res = -1;
        if (!window.isOpen) res = -2;
        Coel::destroy(window);
    }
    
    std::array<Coel::Window, 4> windows;
    for (auto& window : windows) 
        Coel::create(window);

    auto windowsAreOpen = [&windows]() {
        bool isOpen = false;
        for (const auto &window : windows)
            if (window.isOpen) isOpen = true;
        return isOpen;
    };

    while (windowsAreOpen()) {
        for (auto& window : windows) {
            if (window.isOpen) {
                Coel::bind(window);
                Coel::update(window);
            }
        }
    }

    for (auto &window : windows)
        Coel::destroy(window);

    // TODO: Add tests for all window functions
    
    return res;
}
