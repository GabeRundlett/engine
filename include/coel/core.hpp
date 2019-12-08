#pragma once

#include <memory>

namespace coel {
    template <typename T> using Ref = std::shared_ptr<T>;
    template <typename T> using Scope = std::unique_ptr<T>;

    template <typename T, typename... Args> constexpr Ref<T> create_ref(Args &&... args) {
        return std::make_shared<T>(args...);
    }
    template <typename T, typename... Args> constexpr Scope<T> create_scope(Args &&... args) {
        return std::make_unique<T>(args...);
    }
} // namespace coel

#ifndef NDEBUG
#include <iostream>
namespace coel {
    static inline void assert(const bool condition, const char *const value, const char *const file, int line) {
        if (!condition) {
            std::cout << "\033[30;41m ERROR \033[0;31m Assertion failed: \033[0m" << value << " \033[0;90m" << file
                      << ":\033[33m" << line << "\033[0m\n";
        }
    }
} // namespace coel
#define COEL_DEBUG_ONLY(x) x
#define COEL_ASSERT(x) ::coel::assert(x, #x, __FILE__, __LINE__)
#else
#define COEL_DEBUG_ONLY(x)
#define COEL_ASSERT(x)
#endif
