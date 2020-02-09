#pragma once

#include <vector>

namespace Coel {
    struct Element {
        enum Type { F8, I8, U8, F16, I16, U16, F32, I32, U32, F64, I64, U64 };
        Type type;
        unsigned int count;

        static inline constexpr unsigned int toSize(Type t) { return 1 << (t / 3); }
        inline unsigned int getSize() const { return toSize(type) * count; }
    };

    struct Layout {
        std::vector<Element> elements;
        unsigned int stride;

        Layout(const std::initializer_list<Element> &elem) : elements(elem), stride(0) {
            for (const auto elem : elements)
                stride += elem.getSize();
        }
    };

    class Vbo {
        unsigned int m_id;

      public:
        Layout m_layout;

        Vbo() = default;
        Vbo(void *data, unsigned int size, const Layout &l = {});
        ~Vbo();

        void bind() const;
        void setLayout(const Layout &l);
        void open(void *handle) const;
        void close() const;
    };

    class Ibo {
        unsigned int m_id;

      public:
        Ibo() = default;
        Ibo(unsigned short *data, unsigned int size);
        ~Ibo();

        void bind() const;
        void open(void *handle) const;
        void close() const;
    };

    class Vao {
        unsigned int m_id, m_attribCount;

      public:
        Vao();
        ~Vao();

        void bind() const;
        void add(const Vbo &v);

        void draw(unsigned int count) const;
        void drawIndexed(unsigned int count) const;
    };
} // namespace Coel
