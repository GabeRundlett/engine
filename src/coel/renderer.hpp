#pragma once

#include "shader.hpp"
#include "texture.hpp"

namespace coel {
    enum class LayoutType : const unsigned char { Float, Int, UInt, Short, UShort, Byte, UByte };

    struct Model {
        const void *vdata;
        const unsigned short *idata;
        const unsigned int vsize, isize;
        Model(const char *const filepath);
        Model(const void *vdata, const unsigned int vsize, const unsigned short *idata, const unsigned int isize);
    };

    struct Material {
        const Shader *const shader;
        Material() : shader(nullptr){};
        template <typename... T> Material(const Shader *const shader, T... texture_shader_data) : shader(shader) {
            init_tex_mat(shader, 0, texture_shader_data...);
        }

      private:
        static void init_tex_mat(const Shader *const shader, const unsigned int slot, const Texture *texture,
                                 const char *const name);
        template <typename... T>
        inline static void init_tex_mat(const Shader *const shader, const unsigned int slot, const Texture *texture,
                                        const char *const name, T... texture_shader_data) {
            init_tex_mat(shader, slot, texture, name);
            init_tex_mat(shader, slot + 1, texture_shader_data...);
        }
    };

    struct Color {
        unsigned char r, g, b, a;
        constexpr Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a) {}
        constexpr Color(unsigned int hex) : r(char(hex >> 24)), g(char(hex >> 16)), b(char(hex >> 8)), a(char(hex >> 0)) {}
    };
} // namespace coel

namespace coel { namespace renderer {
    void clear();
    void clear_color(const Color &color);
    void clear_color(const float r, const float g, const float b, const float a);
    void viewport(const float width, const float height);
    namespace batch2d {
        struct Vertex {
            float pos_x, pos_y, tex_u, tex_v;
            unsigned char col_r, col_g, col_b, col_a;
            float tid;
        };
        void init(const unsigned int width, const unsigned int height);
        void resize(const unsigned int width, const unsigned int height);
        void fill_color(const Color &color);
        // constexpr arg (template specialization) for whether to center the rect
        void fill_rect(const float pos_x, const float pos_y, const float size_x, const float size_y);
        void flush();
    } // namespace batch2d
    namespace batch3d {
        void init();
        void submit(const Model *const model);
        void flush();
    } // namespace batch3d
    namespace custom {
        void init();
        void submit(const Model *const model);
        void flush();
        void setup_layout(const LayoutType type, const unsigned int count);
        template <typename... P> static inline void setup_layout(const LayoutType type, const unsigned int count, P... param) {
            setup_layout(type, count);
            setup_layout(param...);
        }
        void set_layout(const unsigned int i, const LayoutType type, const unsigned int count);
        template <typename... P>
        static inline void set_layout(const unsigned int i, const LayoutType type, const unsigned int count, P... param) {
            set_layout(i, type, count);
            set_layout(i + 1, param...);
        }
        template <typename... P> static inline void layout(const LayoutType type, const unsigned int count, P... param) {
            renderer::custom::setup_layout(type, count, param...);
            renderer::custom::set_layout(0, type, count, param...);
        }
    } // namespace custom
}}    // namespace coel::renderer
