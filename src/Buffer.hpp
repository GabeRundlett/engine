#pragma once

#include "Core.hpp"
#include "Layout.hpp"
#include "Renderer.hpp"

namespace Coel {
    enum class BufferType : unsigned char { STATIC, DYNAMIC };

    class Vbo {
      public:
        Layout mLayout;

        Vbo(const Layout &layout) : mLayout(layout) {}
        virtual void bind() const = 0;
        virtual void lock() = 0;
        virtual void unlock() = 0;
        virtual size_t getCount() const = 0;
    };

    class Ibo {
      public:
        virtual void bind() const = 0;
        virtual void lock() = 0;
        virtual void unlock() = 0;
        virtual size_t getCount() const = 0;
    };

    class Vao {
      public:
        virtual void bind() const = 0;
        virtual void draw(const Ref<Coel::Ibo> ibo) const = 0;
        virtual void addVbo(const Ref<Vbo> vbo) = 0;
    };

    namespace Opengl {
        class Vbo final : public Coel::Vbo {
            void *mBufferStart, *mBufferPtr;
            COEL_DEBUG_ONLY(BufferType mBufferType);
            COEL_DEBUG_ONLY(bool mLocked);

          public:
            unsigned int mId;
            const size_t mSize;
            size_t mCount;

            Vbo(const void *const data, const size_t size, const Layout &layout);
            void bind() const override;
            void lock() override;
            void unlock() override;
            size_t getCount() const override;
        };

        class Ibo final : public Coel::Ibo {
            unsigned short *mBufferStart, *mBufferPtr;
            COEL_DEBUG_ONLY(BufferType mBufferType);
            COEL_DEBUG_ONLY(bool mLocked);

          public:
            unsigned int mId;
            const size_t mSize;
            size_t mCount;

            Ibo(const unsigned short *const data, const size_t size);

            void bind() const override;
            void lock() override;
            void unlock() override;
            size_t getCount() const override;
        };

        class Vao final : public Coel::Vao {
            unsigned int mId, mAttribCount = 0;

          public:
            Vao();
            void bind() const override;
            void draw(const Ref<Coel::Ibo> ibo) const override;
            void addVbo(const Ref<Coel::Vbo> vbo) override;
        };
    } // namespace Opengl

    static inline Ref<Vbo> createVbo(const void *const data, const size_t size, const Layout &layout) {
        switch (Renderer::getAPI()) {
        case RendererAPI::OPENGL: return createRef<Opengl::Vbo>(data, size, layout);
        case RendererAPI::VULKAN:
        case RendererAPI::DIRECT3D:
        default: return nullptr;
        }
    }
    static inline Ref<Ibo> createIbo(const unsigned short *const data, const size_t size) {
        switch (Renderer::getAPI()) {
        case RendererAPI::OPENGL: return createRef<Opengl::Ibo>(data, size);
        case RendererAPI::VULKAN:
        case RendererAPI::DIRECT3D:
        default: return nullptr;
        }
    }
    static inline Ref<Vao> createVao() {
        switch (Renderer::getAPI()) {
        case RendererAPI::OPENGL: return createRef<Opengl::Vao>();
        case RendererAPI::VULKAN:
        case RendererAPI::DIRECT3D:
        default: return nullptr;
        }
    }
} // namespace Coel
