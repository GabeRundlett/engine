#include <Coel.hpp>

int main() {
    int res = 0;
    for (unsigned int i = 0; i < 5; ++i) {
        Coel::Window window;
        if (Coel::create(window)) res = -1;
        if (!window.isOpen) res = -2;
        // TODO: Add tests for all window functions
        Coel::destroy(window);
    }
    return res;
}
