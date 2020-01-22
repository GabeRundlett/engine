#pragma once

#include <vector>

namespace Coel {
    enum class Type : unsigned char { f32, u8 };

    struct Element {
        const Type type;
        const size_t count, typeSize, size;
        Element(Type t, size_t n) : type(t), count(n), typeSize(toSize(t)), size(typeSize * n) {}

        static inline constexpr size_t toSize(const Type &t) {
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
} // namespace Coel
