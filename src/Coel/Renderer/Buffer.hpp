#pragma once

#include <vector>

namespace Coel {
    enum Type { F8, I8, U8, F16, I16, U16, F32, I32, U32, F64, I64, U64 };
    struct Element {
        unsigned int type, count;

        static inline constexpr unsigned int toSize(unsigned int t) { return 1 << (t / 3); }
        inline unsigned int getSize() const { return toSize(type) * count; }
    };

    struct Layout {
        std::vector<Element> elements{};
        unsigned int stride{};

        Layout(const std::initializer_list<Element> &elem) : elements(elem) {
            for (const auto elem : elements)
                stride += elem.getSize();
        }
    };

    namespace ColorBuffer {
        enum Format { RGB8, RGB16, RGBA8, RGBA16, Float };
    }

    namespace DepthBuffer {
        enum Format { None, Float16, Float32, RenderBuffer };
    }

    class Fbo {
        unsigned int m_id, m_colTexId[4], m_depTexId, m_depRboId, m_width, m_height;
        unsigned char m_colorAttachments[4], m_colorAttachmentCount, m_depthAttachment;

      public:
        Fbo(unsigned int width, unsigned int height, const std::initializer_list<unsigned char> &colorAttachments,
            const unsigned char depthAttachment = DepthBuffer::RenderBuffer);
        ~Fbo();

        void bind() const;
        static void unbind();
        void bindColorAttachmentTexture(int attachment, int slot) const;
        void bindDepthTexture(int slot) const;
    };

    struct Vbo {
        Layout layout{};
        unsigned int id{};
    };

    void create(Vbo &vbo, void *data, unsigned int size);
    void destroy(Vbo &vbo);
    void bind(const Vbo &vbo);
    void setLayout(Vbo &vbo, const Layout &l);
    void open(const Vbo &vbo, void *handle);
    void close(const Vbo &vbo);

    struct Ibo {
        unsigned int id{};
    };

    void create(Ibo &ibo, void *data, unsigned int size);
    void destroy(Ibo &ibo);
    void bind(const Ibo &ibo);
    void open(const Ibo &ibo, void *handle);
    void close(const Ibo &ibo);

    struct Vao {
        unsigned int id{}, attribCount{};
    };

    void create(Vao &vao);
    void destroy(Vao &vao);
    void bind(const Vao &vao);
    void link(Vao &vao, const Vbo &vbo);
} // namespace Coel
