#pragma once

#include <memory>

namespace Coel {
    template <typename T> using Ref = std::shared_ptr<T>;
    template <typename T> using Scope = std::unique_ptr<T>;

    template <typename T, typename... Args> constexpr Ref<T> createRef(Args &&... args) { return std::make_shared<T>(args...); }
    template <typename T, typename... Args> constexpr Scope<T> createScope(Args &&... args) {
        return std::make_unique<T>(args...);
    }
} // namespace Coel

#ifndef NDEBUG
#include <iostream>
namespace Coel {
    static inline void assert(const bool condition, const char *const value, const char *const file, int line) {
        if (!condition) {
            std::cout << "\033[30;41m ERROR \033[0;31m Assertion failed: \033[0m" << value << " \033[0;90m" << file
                      << ":\033[33m" << line << "\033[0m\n";
        }
    }
} // namespace Coel
#define COEL_DEBUG_ONLY(x) x
#define COEL_ASSERT(x) ::Coel::assert(x, #x, __FILE__, __LINE__)
#else
#define COEL_DEBUG_ONLY(x)
#define COEL_ASSERT(x)
#endif
