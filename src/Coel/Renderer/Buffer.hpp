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

    struct Buffer {
        enum Type {
            None = 0,
            Color = 1 << 0,
            Depth = 1 << 1,
            RenderDepth = 1 << 2,
        };
    };

    class Fbo {
        unsigned int m_id, m_colTexId, m_depTexId, m_depRboId, m_width, m_height;
        unsigned char m_flags;

      public:
        Fbo(unsigned int width, unsigned int height, unsigned char flags);
        ~Fbo();

        void bind() const;
        static void unbind();
        void bindColorTexture(int slot) const;
        void bindDepthTexture(int slot) const;
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
        Ibo(unsigned int *data, unsigned int size);
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
