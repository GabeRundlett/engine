#include "Common.hpp"
#include "../Buffer.hpp"

namespace Coel { namespace Opengl {
    Vbo::Vbo(const void *const data, const size_t size, const Layout &layout) : mSize(size), ::Coel::Vbo(layout) {
        // DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(glGenBuffers(1, &mId));
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, mId));
        if (data) {
            mCount = size / mLayout.stride;
            COEL_DEBUG_ONLY(mBufferType = BufferType::STATIC);
            GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
            mBufferStart = nullptr, mBufferPtr = nullptr;
            COEL_DEBUG_ONLY(mLocked = true);
        } else {
            mCount = 0;
            COEL_DEBUG_ONLY(mBufferType = BufferType::DYNAMIC);
            GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
            GL_CALL(mBufferStart = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
            mBufferPtr = mBufferStart;
            COEL_DEBUG_ONLY(mLocked = false);
        }
    }

    void Vbo::bind() const {
        // DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, mId));
    }

    void Vbo::lock() {
        // DEBUG_BEGIN_FUNC_PROFILE;

        COEL_ASSERT(!mLocked);
        COEL_ASSERT(mBufferType == BufferType::DYNAMIC);
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, mId));
        GL_CALL(glUnmapBuffer(GL_ARRAY_BUFFER));
        COEL_DEBUG_ONLY(mLocked = true);
    }

    void Vbo::unlock() {
        // DEBUG_BEGIN_FUNC_PROFILE;

        COEL_ASSERT(mLocked);
        COEL_ASSERT(mBufferType == BufferType::DYNAMIC);
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, mId));
        GL_CALL(mBufferStart = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
        mBufferPtr = mBufferStart;
        COEL_DEBUG_ONLY(mLocked = false);
    }

    size_t Vbo::getCount() const {
        // DEBUG_BEGIN_FUNC_PROFILE;

        return mCount;
    }

    Ibo::Ibo(const unsigned short *const data, const size_t size) : mSize(size) {
        // DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(glGenBuffers(1, &mId));
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, mId));
        if (data) {
            mCount = size / sizeof(unsigned short);
            COEL_DEBUG_ONLY(mBufferType = BufferType::STATIC);
            GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
            mBufferStart = nullptr, mBufferPtr = nullptr;
            COEL_DEBUG_ONLY(mLocked = true);
        } else {
            mCount = 0;
            COEL_DEBUG_ONLY(mBufferType = BufferType::DYNAMIC);
            GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
            GL_CALL(mBufferStart = reinterpret_cast<unsigned short *>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY)));
            mBufferPtr = mBufferStart;
            COEL_DEBUG_ONLY(mLocked = false);
        }
    }

    void Ibo::bind() const {
        // DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId));
    }

    void Ibo::lock() {
        // DEBUG_BEGIN_FUNC_PROFILE;

        COEL_ASSERT(!mLocked);
        COEL_ASSERT(mBufferType == BufferType::DYNAMIC);
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId));
        GL_CALL(glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER));
        COEL_DEBUG_ONLY(mLocked = true);
    }

    void Ibo::unlock() {
        // DEBUG_BEGIN_FUNC_PROFILE;

        COEL_ASSERT(mLocked);
        COEL_ASSERT(mBufferType == BufferType::DYNAMIC);
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId));
        GL_CALL(mBufferStart = reinterpret_cast<unsigned short *>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY)));
        mBufferPtr = mBufferStart;
        COEL_DEBUG_ONLY(mLocked = false);
    }

    size_t Ibo::getCount() const {
        // DEBUG_BEGIN_FUNC_PROFILE;

        return mCount;
    }

    static inline constexpr GLenum toOpenglType(const Type type) {
        switch (type) {
        case Type::f32: return GL_FLOAT;
        case Type::u8: return GL_UNSIGNED_BYTE;
        default: return 0;
        }
    }

    Vao::Vao() {
        // DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(glGenVertexArrays(1, &mId));
        GL_CALL(glBindVertexArray(mId));
    }

    void Vao::bind() const {
        // DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(glBindVertexArray(mId));
    }

    void Vao::draw(const Ref<Coel::Ibo> ibo) const {
        // DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(glBindVertexArray(mId));
        ibo->bind();
        GL_CALL(glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(ibo->getCount()), GL_UNSIGNED_SHORT, nullptr));
    }

    void Vao::addVbo(const Ref<Coel::Vbo> vbo) {
        // DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(glBindVertexArray(mId));
        vbo->bind();
        unsigned char *offset = nullptr;
        for (const auto elem : vbo->mLayout.elements) {
            GL_CALL(glEnableVertexAttribArray(mAttribCount));
            GL_CALL(glVertexAttribPointer(mAttribCount, static_cast<GLint>(elem.count), toOpenglType(elem.type), GL_FALSE,
                                          static_cast<GLsizei>(vbo->mLayout.stride), offset));
            offset += elem.size;
            ++mAttribCount;
        }
    }
}} // namespace Coel::Opengl
