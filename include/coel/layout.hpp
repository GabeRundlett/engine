#pragma once

#include <vector>

namespace coel {
    enum class Type : unsigned char { f32, u8 };

    struct Element {
        const Type type;
        const size_t count, type_size, size;
        Element(Type t, size_t n) : type(t), count(n), type_size(to_size(t)), size(type_size * n) {}

        static inline constexpr size_t to_size(const Type t) {
            switch (t) {
            case Type::f32: return 4;
            case Type::u8: return 1;
            default: return 0;
            }
        }
    };

    struct Layout {
        std::vector<Element> elements;
        size_t stride;

        Layout(const std::initializer_list<Element> &elem) : elements(elem), stride(0) {
            for (const auto elem : elements)
                stride += elem.size;
        }
    };
} // namespace coel
