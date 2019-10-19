#pragma once

#include "shader.hpp"
#include "texture.hpp"

#include "../dep/math/src/math.hpp"

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
    void clear();
    void clear_color(const math::Color &color);
    void clear_color(const float r, const float g, const float b, const float a);
    void viewport(const float width, const float height);
    namespace batch2d {
        void init(const unsigned int width, const unsigned int height);
        void resize(const unsigned int width, const unsigned int height);
        void fill_color(const math::Color &color);
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
