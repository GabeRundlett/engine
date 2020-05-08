#pragma once

#include <vector>
#include <cstdint>
#include <glm/glm.hpp>
#include <Coel/Renderer/Texture.hpp>

namespace Coel {
    enum ElementType {
        F8,
        I8,
        U8,
        F16,
        I16,
        U16,
        F32,
        I32,
        U32,
        F64,
        I64,
        U64,
    };
    static inline constexpr uint32_t toSize(const ElementType t) { return 1 << (t / 3); }
    struct Element {
        ElementType type;
        uint32_t count;
        inline constexpr uint32_t getSize() const { return toSize(type) * count; }
    };

    struct Layout {
        std::vector<Element> elements{};
        uint32_t stride{};
        Layout(const std::initializer_list<Element> &elem) : elements(elem) {
            for (const auto e : elements)
                stride += e.getSize();
        }
    };

    struct Vbo {
        Layout layout{};
        uint32_t id{};
    };

    void create(Vbo &vbo, void *data, const uint32_t size);
    void destroy(Vbo &vbo);
    void bind(const Vbo &vbo);
    void open(const Vbo &vbo, void *handle);
    void close(const Vbo &vbo);

    struct Ibo {
        uint32_t id{};
    };

    void create(Ibo &ibo, void *data, const uint32_t size);
    void destroy(Ibo &ibo);
    void bind(const Ibo &ibo);
    void open(const Ibo &ibo, void *handle);
    void close(const Ibo &ibo);

    struct Vao {
        uint32_t id{}, attribCount{};
    };

    void create(Vao &vao);
    void destroy(Vao &vao);
    void bind(const Vao &vao);
    void link(Vao &vao, const Vbo &vbo);

    struct Rbo {
        uint32_t id;
        glm::ivec2 size;
    };

    void create(Rbo &rbo, const glm::ivec2 &size);
    void destroy(Rbo &rbo);

    struct Fbo {
        uint32_t id;
        glm::ivec2 size;
    };

    void create(Fbo &fbo, const glm::ivec2 &size);
    void bind(const Fbo &fbo);
    void attach(Fbo &fbo, const std::initializer_list<Texture> &attachments);
    void attach(Fbo &fbo, const Rbo &rbo);
    void destroy(Fbo &fbo);
} // namespace Coel
