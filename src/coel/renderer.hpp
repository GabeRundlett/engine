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
} // namespace coel

namespace coel { namespace renderer {
    void clear(const unsigned int color);
    void clear(const float r, const float g, const float b, const float a = 1.f);
    static inline void clear(const float val = 0.25) { clear(val, val, val, 1.f); }
    void viewport(const float width, const float height);
    namespace batch2d {
        struct Vertex {
            float pos_x, pos_y, tex_u, tex_v;
            unsigned char col_r, col_g, col_b, col_a;
            float tid;
        };
        void init(const unsigned int width, const unsigned int height);
        void resize(const unsigned int width, const unsigned int height);
        // constexpr arg (template specialization) for whether to center the rect
        void submit_rect(const float pos_x, const float pos_y, const float size_x, const float size_y, const float tid = -1.f);
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
