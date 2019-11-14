#pragma once

#include "../core.hpp"
#include "../layout.hpp"
#include "../renderer.hpp"

namespace coel {
    enum class BufferType : unsigned char { Static, Dynamic };

    class Vbo {
      public:
        Layout m_layout;
        Vbo(const Layout &layout) : m_layout(layout) {}
        virtual void bind() const = 0;
        virtual void lock() = 0;
        virtual void unlock() = 0;
        virtual size_t get_count() const = 0;
    };

    class Ibo {
      public:
        virtual void bind() const = 0;
        virtual void lock() = 0;
        virtual void unlock() = 0;
        virtual size_t get_count() const = 0;
    };

    class Vao {
      public:
        virtual void bind() const = 0;
        virtual void draw(const Ref<coel::Ibo> ibo) const = 0;
        virtual void add_vbo(const Ref<Vbo> vbo) = 0;
    };

    namespace opengl {
        class Vbo final : public coel::Vbo {
            void *m_buffer_start, *m_buffer_pointer;
            COEL_DEBUG_ONLY(BufferType m_buffertype);
            COEL_DEBUG_ONLY(bool m_locked);

          public:
            unsigned int m_id;
            const size_t m_size;
            size_t m_count;

            Vbo(const void *const data, const size_t size, const Layout &layout);
            void bind() const override;
            void lock() override;
            void unlock() override;
            size_t get_count() const override;
        };

        class Ibo final : public coel::Ibo {
            unsigned short *m_buffer_start, *m_buffer_pointer;
            COEL_DEBUG_ONLY(BufferType m_buffertype);
            COEL_DEBUG_ONLY(bool m_locked);

          public:
            unsigned int m_id;
            const size_t m_size;
            size_t m_count;

            Ibo(const unsigned short *const data, const size_t size);

            void bind() const override;
            void lock() override;
            void unlock() override;
            size_t get_count() const override;
        };

        class Vao final : public coel::Vao {
            unsigned int m_id, m_attrib_count = 0;

          public:
            Vao();
            void bind() const override;
            void draw(const Ref<coel::Ibo> ibo) const override;
            void add_vbo(const Ref<coel::Vbo> vbo) override;
        };
    } // namespace opengl

    static inline Ref<Vbo> create_vbo(const void *const data, const size_t size, const Layout &layout) {
        switch (Renderer::get_api()) {
        case RendererAPI::OpenGL: return create_ref<opengl::Vbo>(data, size, layout);
        case RendererAPI::Vulkan:
        case RendererAPI::Direct3D:
        default: return nullptr;
        }
    }
    static inline Ref<Ibo> create_ibo(const unsigned short *const data, const size_t size) {
        switch (Renderer::get_api()) {
        case RendererAPI::OpenGL: return create_ref<opengl::Ibo>(data, size);
        case RendererAPI::Vulkan:
        case RendererAPI::Direct3D:
        default: return nullptr;
        }
    }
    static inline Ref<Vao> create_vao() {
        switch (Renderer::get_api()) {
        case RendererAPI::OpenGL: return create_ref<opengl::Vao>();
        case RendererAPI::Vulkan:
        case RendererAPI::Direct3D:
        default: return nullptr;
        }
    }
} // namespace coel
