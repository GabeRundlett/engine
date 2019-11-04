#include "../../coel.hpp"
#include "../texture.hpp"
#include <glad/glad.h>
#include <string.h>

namespace coel { namespace renderer { namespace batch2d {
    struct Sprite {
        math::Vec3 pos;
        math::Vec2 size;
        math::Color col;
        float mat;
        math::Vec4 data1, data2;
    };

    static constexpr unsigned int s_sprite_max = 100000, s_vbuffer_size = sizeof(Sprite) * s_sprite_max;
    static unsigned int s_vao_id, s_vbo_id;
    static unsigned int s_sprite_count = 0;
    static Sprite *s_vbuffer_pointer;
    static math::Vec2 s_viewport;
    static math::Color s_fill_color = {255, 0, 255, 255};

    static Texture arial_sdf;

    struct BitmapCharData {
        float u, v, s, t, x_off, y_off, x_adv;
    };

    static constexpr BitmapCharData arial_bcd[] = {
        {362, 505, 4, 4, 1.500, 1.500, 23.063},    {361, 381, 12, 63, 5.938, 60.875, 23.000},
        {487, 0, 25, 25, 2.313, 60.875, 29.438},   {202, 257, 48, 65, 0.625, 61.938, 46.188},
        {318, 381, 43, 77, 1.438, 66.375, 46.125}, {80, 63, 67, 66, 3.313, 61.875, 73.813},
        {432, 383, 53, 65, 2.063, 61.938, 55.313}, {185, 450, 12, 25, 2.125, 60.875, 15.813},
        {0, 243, 23, 81, 3.500, 61.938, 27.625},   {23, 243, 23, 81, 3.500, 61.938, 27.625},
        {27, 190, 30, 29, 1.063, 61.938, 32.313},  {368, 0, 43, 43, 3.125, 50.375, 48.500},
        {185, 475, 12, 24, 5.375, 9.813, 23.063},  {262, 177, 26, 11, 1.125, 26.625, 27.688},
        {361, 444, 12, 12, 6.063, 9.813, 23.063},  {23, 324, 27, 65, 1.500, 61.938, 23.063},
        {80, 262, 42, 64, 1.938, 61.188, 46.188},  {485, 448, 25, 63, 7.500, 61.125, 46.188},
        {387, 129, 43, 63, 1.000, 61.125, 46.188}, {80, 198, 42, 64, 2.000, 61.125, 46.188},
        {464, 192, 45, 63, 0.438, 60.875, 46.188}, {202, 449, 43, 63, 1.938, 60.125, 46.188},
        {142, 258, 43, 64, 1.625, 61.125, 46.188}, {430, 129, 42, 62, 2.438, 60.125, 46.125},
        {142, 194, 43, 64, 1.875, 61.125, 46.125}, {202, 385, 43, 64, 1.938, 61.188, 46.125},
        {362, 458, 12, 47, 6.000, 44.500, 23.063}, {245, 449, 12, 58, 5.375, 44.500, 23.063},
        {243, 0, 43, 44, 3.063, 50.938, 48.500},   {27, 162, 43, 28, 3.125, 43.188, 48.500},
        {286, 0, 43, 44, 3.063, 50.938, 48.500},   {142, 386, 42, 64, 2.125, 61.938, 46.188},
        {0, 0, 80, 81, 3.000, 62.000, 84.250},     {260, 192, 59, 63, 1.625, 60.938, 55.375},
        {368, 192, 48, 63, 4.563, 60.875, 55.375}, {376, 318, 56, 65, 2.625, 61.938, 59.938},
        {432, 448, 53, 63, 4.875, 60.875, 59.938}, {416, 192, 48, 63, 5.063, 60.875, 55.375},
        {202, 322, 44, 63, 5.313, 60.938, 50.688}, {202, 192, 58, 65, 2.938, 61.938, 64.563},
        {260, 382, 50, 63, 5.125, 60.875, 59.938}, {184, 386, 11, 63, 6.250, 60.875, 23.063},
        {350, 63, 36, 64, 0.813, 60.938, 41.500},  {376, 446, 53, 63, 4.563, 60.875, 55.375},
        {270, 63, 41, 63, 4.563, 60.938, 46.125},  {202, 129, 60, 63, 4.688, 60.875, 69.188},
        {260, 445, 50, 63, 4.813, 60.875, 59.938}, {142, 129, 60, 65, 2.500, 61.938, 64.563},
        {319, 192, 49, 63, 4.875, 60.875, 55.375}, {80, 129, 62, 69, 2.063, 61.938, 64.563},
        {376, 383, 56, 63, 5.000, 60.875, 59.938}, {432, 318, 51, 65, 2.313, 61.938, 55.313},
        {427, 255, 51, 63, 0.438, 60.875, 50.688}, {260, 318, 50, 64, 5.000, 60.938, 59.938},
        {260, 255, 58, 63, 1.188, 60.938, 55.375}, {80, 0, 80, 63, 0.500, 60.938, 78.313},
        {318, 255, 58, 63, 1.188, 60.875, 55.375}, {318, 318, 58, 63, 1.313, 60.938, 55.375},
        {376, 255, 51, 63, 0.188, 60.875, 50.750}, {46, 243, 20, 79, 4.125, 60.875, 23.063},
        {485, 383, 27, 65, 1.500, 61.938, 23.063}, {43, 389, 20, 79, 0.063, 60.875, 23.063},
        {449, 0, 38, 36, 0.688, 61.938, 38.938},   {324, 176, 52, 9, 2.750, 9.750, 46.188},
        {288, 177, 19, 15, 2.063, 61.250, 27.625}, {142, 450, 43, 49, 1.500, 45.500, 46.125},
        {80, 391, 41, 64, 3.938, 60.875, 46.125},  {160, 0, 41, 49, 1.750, 45.500, 41.500},
        {147, 63, 41, 64, 1.313, 60.875, 46.125},  {80, 455, 43, 49, 1.563, 45.500, 46.188},
        {483, 318, 29, 64, 0.750, 61.938, 23.000}, {80, 326, 41, 65, 1.188, 45.563, 46.188},
        {472, 129, 39, 63, 4.000, 60.875, 46.188}, {246, 322, 11, 63, 4.000, 60.875, 18.438},
        {23, 389, 20, 80, 5.313, 60.875, 18.438},  {311, 63, 39, 63, 4.000, 60.875, 41.500},
        {245, 385, 11, 63, 3.813, 60.875, 18.438}, {262, 129, 62, 48, 4.000, 45.500, 69.188},
        {329, 0, 39, 48, 4.000, 45.500, 46.188},   {318, 458, 44, 49, 1.250, 45.500, 46.125},
        {229, 63, 41, 64, 4.000, 45.500, 46.188},  {188, 63, 41, 64, 1.438, 45.500, 46.188},
        {50, 324, 27, 48, 3.875, 45.500, 27.625},  {473, 63, 39, 49, 1.000, 45.500, 41.438},
        {478, 255, 25, 62, 0.063, 59.625, 23.063}, {411, 0, 38, 48, 3.813, 44.500, 46.125},
        {430, 63, 43, 47, 0.500, 44.563, 41.500},  {324, 129, 63, 47, 1.313, 44.563, 59.938},
        {386, 63, 44, 47, 0.938, 44.500, 41.500},  {142, 322, 43, 64, 0.188, 44.563, 41.500},
        {201, 0, 42, 47, 0.125, 44.563, 41.563},   {0, 81, 27, 81, 0.813, 61.938, 27.688},
        {63, 389, 10, 81, 6.125, 61.938, 21.563},  {0, 162, 27, 81, 0.375, 61.938, 27.750},
        {449, 36, 45, 17, 2.000, 37.375, 48.438},
    };
    static Shader s_shader;
    static constexpr char *const s_vertex_shader_source =
#include "shaders/batch2d_vs.glsl"
                                     "",
                                 *const s_geometry_shader_source =
#include "shaders/batch2d_gs.glsl"
                                     "",
                                 *const s_fragment_shader_source =
#include "shaders/batch2d_fs.glsl"
                                     "";

    void init(const unsigned int width, const unsigned int height) {
        glGenVertexArrays(1, &s_vao_id);
        glBindVertexArray(s_vao_id);

        glGenBuffers(1, &s_vbo_id);
        glBindBuffer(GL_ARRAY_BUFFER, s_vbo_id);
        glBufferData(GL_ARRAY_BUFFER, s_vbuffer_size, nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glEnableVertexAttribArray(4);
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Sprite), (const void *)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Sprite), (const void *)12);
        glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Sprite), (const void *)20);
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Sprite), (const void *)24);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Sprite), (const void *)28);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Sprite), (const void *)44);

        s_vbuffer_pointer = reinterpret_cast<Sprite *>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

        s_shader = shader::create(ShaderType::Vertex, s_vertex_shader_source, ShaderType::Geometry, s_geometry_shader_source,
                                  ShaderType::Fragment, s_fragment_shader_source);
        resize(width, height);

        arial_sdf = texture::create("arial_sdf.png");
    }

    void resize(const unsigned int width, const unsigned int height) {
        s_viewport.x = width, s_viewport.y = height;
        shader::send_float2(s_shader, "window_size", &s_viewport);
    }

    void fill_color(const math::Color &color) { s_fill_color = color; }

    void fill_rect(const Rect &r) {
        s_vbuffer_pointer->pos = r.pos;
        s_vbuffer_pointer->size = r.size;
        s_vbuffer_pointer->col = s_fill_color;
        s_vbuffer_pointer->mat = 0.f;
        s_vbuffer_pointer->data1 = r.data1;
        s_vbuffer_pointer->data2 = r.data2;
        ++s_vbuffer_pointer;
        ++s_sprite_count;
        if (s_sprite_count > s_sprite_max) flush();
    }

    void fill_ellipse(const Ellipse &e) {
        s_vbuffer_pointer->pos = e.pos;
        s_vbuffer_pointer->size = e.size;
        s_vbuffer_pointer->col = s_fill_color;
        s_vbuffer_pointer->mat = 2.f;
        s_vbuffer_pointer->data1 = e.data1;
        s_vbuffer_pointer->data2 = e.data2;
        ++s_vbuffer_pointer;
        ++s_sprite_count;
        if (s_sprite_count > s_sprite_max) flush();
    }

    void fill_line(const Line &l) {
        s_vbuffer_pointer->pos = {l.a.x, l.a.y, 0.f};
        s_vbuffer_pointer->size = l.b - l.a;
        s_vbuffer_pointer->col = s_fill_color;
        s_vbuffer_pointer->mat = 3.f;
        s_vbuffer_pointer->data1 = l.data1;
        s_vbuffer_pointer->data2 = l.data2;
        ++s_vbuffer_pointer;
        ++s_sprite_count;
        if (s_sprite_count > s_sprite_max) flush();
    }

    void fill_text(const Text &t) {
        const unsigned int len = strlen(t.text);
        float cursor = t.pos.x;
        for (unsigned int i = 0; i < len; ++i) {
            const char cid = t.text[i];
            constexpr float scale = 14.f / 59;
            const BitmapCharData &temp_bcd = arial_bcd[cid - 32];
            s_vbuffer_pointer->pos = {cursor + temp_bcd.x_off * scale, t.pos.y - temp_bcd.y_off * scale, 0.f};
            s_vbuffer_pointer->size = {temp_bcd.s * scale, temp_bcd.t * scale};
            s_vbuffer_pointer->col = s_fill_color;
            s_vbuffer_pointer->mat = 4.f;
            s_vbuffer_pointer->data1 = {temp_bcd.u, temp_bcd.v, temp_bcd.x_off, temp_bcd.y_off};
            s_vbuffer_pointer->data2 = {temp_bcd.s, temp_bcd.t, temp_bcd.x_adv, 0.f};
            ++s_vbuffer_pointer;
            ++s_sprite_count;
            if (s_sprite_count > s_sprite_max) flush();
            cursor += temp_bcd.x_adv * scale;
        }
    }

    void flush() {
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glBindVertexArray(s_vao_id);
        shader::bind(s_shader);
        glDrawArrays(GL_POINTS, 0, s_sprite_count);
        s_vbuffer_pointer = reinterpret_cast<Sprite *>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
        s_sprite_count = 0;
    }
}}} // namespace coel::renderer::batch2d

/*
color = f.col;
const float radius = f.data.x;
if (uv.x < radius) {
if (uv.y < radius) {
    color.w *= circle_alpha(vec2(radius, radius), radius);
    color.w = gradient_transform(color.w);
} else if (uv.y > size.y - radius) {
    color.w *= circle_alpha(vec2(radius, size.y - radius), radius);
    color.w = gradient_transform(color.w);
} else {
    color.w *= clamp(uv.x / radius, 0, 1);
    color.w = gradient_transform(color.w);
}
} else if (uv.x > size.x - radius) {
if (uv.y < radius) {
    color.w *= circle_alpha(vec2(size.x - radius, radius), radius);
    color.w = gradient_transform(color.w);
} else if (uv.y > size.y - radius) {
    color.w *= circle_alpha(vec2(size.x - radius, size.y - radius), radius);
    color.w = gradient_transform(color.w);
} else {
    color.w *= clamp((size.x - uv.x) / radius, 0, 1);
    color.w = gradient_transform(color.w);
}
} else if (uv.y < radius) {
    color.w *= clamp(uv.y / radius, 0, 1);
    color.w = gradient_transform(color.w);
} else if (uv.y > size.y - radius) {
    color.w *= clamp((size.y - uv.y) / radius, 0, 1);
    color.w = gradient_transform(color.w);
}

ROUNDED CORNERS
if (f.tid == 0.f) {
    const float radius = f.data.x;
    color = f.col;
    if (uv.x < f.data.x && uv.y < f.data.x) {
        color.w *= clamp(circle_alpha(vec2(f.data.x, f.data.x), f.data.x) * f.data.x * 2, 0, 1);
    } else if (uv.x < f.data.y && uv.y > size.y - f.data.y) {
        color.w *= clamp(circle_alpha(vec2(f.data.y, size.y - f.data.y), f.data.y) * f.data.y * 2, 0, 1);
    } else if (uv.x > size.x - f.data.z && uv.y < f.data.z) {
        color.w *= clamp(circle_alpha(vec2(size.x - f.data.z, f.data.z), f.data.z) * f.data.z * 2, 0, 1);
    } else if (uv.x > size.x - f.data.w && uv.y > size.y - f.data.w) {
        color.w *= clamp(circle_alpha(vec2(size.x - f.data.w, size.y - f.data.w), f.data.w) * f.data.w * 2, 0, 1);
    }
} else if (f.tid == 1.f) {
    color = f.col;
    if (uv.x < f.data.x && uv.y < f.data.x) {
        color.w *= clamp(circle_alpha(vec2(f.data.x, f.data.x), f.data.x) * f.data.x * 2, 0, 1);
    } else if (uv.x < f.data.y && uv.y > size.y - f.data.y) {
        color.w *= clamp(circle_alpha(vec2(f.data.y, size.y - f.data.y), f.data.y) * f.data.y * 2, 0, 1);
    } else if (uv.x > size.x - f.data.z && uv.y < f.data.z) {
        color.w *= clamp(circle_alpha(vec2(size.x - f.data.z, f.data.z), f.data.z) * f.data.z * 2, 0, 1);
    } else if (uv.x > size.x - f.data.w && uv.y > size.y - f.data.w) {
        color.w *= clamp(circle_alpha(vec2(size.x - f.data.w, size.y - f.data.w), f.data.w) * f.data.w * 2, 0, 1);
    }
}



VERTEX


layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 size;
layout(location = 2) in vec4 col;
layout(location = 3) in vec4 data;
layout(location = 4) in float tid;

uniform vec2 window_size;

out VS_OUT {
        vec2 size;
        vec4 col;
        vec4 data;
        float tid;
} v;

void main() {
        v.size = vec2(size.x / window_size.x * 2.f, size.y / window_size.y * -2.f);
    v.col = col / 255;
    v.data = data;
    v.tid = tid;

        if (tid == 0.f || tid == 1.f) {
                if (v.data.x > size.x / 2) v.data.x = size.x / 2;
                if (v.data.x > size.y / 2) v.data.x = size.y / 2;

                if (v.data.y > size.x / 2) v.data.y = size.x / 2;
                if (v.data.y > size.y / 2) v.data.y = size.y / 2;

                if (v.data.z > size.x / 2) v.data.z = size.x / 2;
                if (v.data.z > size.y / 2) v.data.z = size.y / 2;

                if (v.data.w > size.x / 2) v.data.w = size.x / 2;
                if (v.data.w > size.y / 2) v.data.w = size.y / 2;
        }

        gl_Position = vec4(pos.x / window_size.x * 2.f - 1, pos.y / window_size.y * -2.f + 1, pos.z / 1000, 1);
        if (gl_Position.z < 0.f) gl_Position.z = 0.f;
}

GEOMETRY

#version 440

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

const float blur_rate = 32 * 1000;

in VS_OUT {
        vec2 size;
        vec4 col;
        vec4 data;
        float tid;
} g_i[];

uniform vec2 window_size;

out GS_OUT {
        vec2 size;
        vec2 tex;
        vec4 col;
        vec4 data;
        vec4 data2;
        float tid;
} g_o;

void main() {
        gl_Position = gl_in[0].gl_Position + vec4(0, 0);
        g_o.size = g_i[0].size;
        g_o.tex = vec2(0, 0);
        g_o.col = g_i[0].col;
        g_o.data = g_i[0].data;
        g_o.tid = g_i[0].tid;
        if (g_o.tid == 0.f || g_o.tid == 1.f) {
                gl_Position += vec4(-blur_rate * gl_in[0].gl_Position.z / window_size.x *  2,
                                                        -blur_rate * gl_in[0].gl_Position.z / window_size.y * -2);
                g_o.data += vec4(
                        blur_rate * gl_in[0].gl_Position.z / window_size.x * 4,
                        blur_rate * gl_in[0].gl_Position.z / window_size.y * 4,
                        blur_rate * gl_in[0].gl_Position.z / window_size.x * 4,
                        blur_rate * gl_in[0].gl_Position.z / window_size.y * 4
                );
                g_o.data2.xy = g_o.size, g_o.data2.z = gl_in[0].gl_Position.z;
                g_o.size += vec2(blur_rate * gl_in[0].gl_Position.z / window_size.x * 4,
                                                 blur_rate * gl_in[0].gl_Position.z / window_size.y * -4);
        }
        EmitVertex();
        gl_Position = gl_in[0].gl_Position + vec4(g_i[0].size.x, 0);
        g_o.size = g_i[0].size;
        g_o.tex = vec2(1, 0);
        g_o.col = g_i[0].col;
        g_o.data = g_i[0].data;
        g_o.tid = g_i[0].tid;

        if (g_o.tid == 0.f || g_o.tid == 1.f) {
                gl_Position += vec4( blur_rate * gl_in[0].gl_Position.z / window_size.x *  2,
                                                        -blur_rate * gl_in[0].gl_Position.z / window_size.y * -2);
                g_o.data += vec4(
                        blur_rate * gl_in[0].gl_Position.z / window_size.x * 4,
                        blur_rate * gl_in[0].gl_Position.z / window_size.y * 4,
                        blur_rate * gl_in[0].gl_Position.z / window_size.x * 4,
                        blur_rate * gl_in[0].gl_Position.z / window_size.y * 4
                );
                g_o.data2.xy = g_o.size, g_o.data2.z = gl_in[0].gl_Position.z;
                g_o.size += vec2(blur_rate * gl_in[0].gl_Position.z / window_size.x * 4,
                                                 blur_rate * gl_in[0].gl_Position.z / window_size.y * -4);
        }
        EmitVertex();
        gl_Position = gl_in[0].gl_Position + vec4(0, g_i[0].size.y);
        g_o.size = g_i[0].size;
        g_o.tex = vec2(0, 1);
        g_o.col = g_i[0].col;
        g_o.data = g_i[0].data;
        g_o.tid = g_i[0].tid;
        if (g_o.tid == 0.f || g_o.tid == 1.f) {
                gl_Position += vec4(-blur_rate * gl_in[0].gl_Position.z / window_size.x *  2,
                                                         blur_rate * gl_in[0].gl_Position.z / window_size.y * -2);
                g_o.data += vec4(
                        blur_rate * gl_in[0].gl_Position.z / window_size.x * 4,
                        blur_rate * gl_in[0].gl_Position.z / window_size.y * 4,
                        blur_rate * gl_in[0].gl_Position.z / window_size.x * 4,
                        blur_rate * gl_in[0].gl_Position.z / window_size.y * 4
                );
                g_o.data2.xy = g_o.size, g_o.data2.z = gl_in[0].gl_Position.z;
                g_o.size += vec2(blur_rate * gl_in[0].gl_Position.z / window_size.x * 4,
                                                 blur_rate * gl_in[0].gl_Position.z / window_size.y * -4);
        }
        EmitVertex();
        gl_Position = gl_in[0].gl_Position + vec4(g_i[0].size.x, g_i[0].size.y);
        g_o.size = g_i[0].size;
        g_o.tex = vec2(1, 1);
        g_o.col = g_i[0].col;
        g_o.data = g_i[0].data;
        g_o.tid = g_i[0].tid;
        if (g_o.tid == 0.f || g_o.tid == 1.f) {
                gl_Position += vec4(blur_rate * gl_in[0].gl_Position.z / window_size.x *  2,
                                                        blur_rate * gl_in[0].gl_Position.z / window_size.y * -2);
                g_o.data += vec4(
                        blur_rate * gl_in[0].gl_Position.z / window_size.x * 4,
                        blur_rate * gl_in[0].gl_Position.z / window_size.y * 4,
                        blur_rate * gl_in[0].gl_Position.z / window_size.x * 4,
                        blur_rate * gl_in[0].gl_Position.z / window_size.y * 4
                );
                g_o.data2.xy = g_o.size, g_o.data2.z = gl_in[0].gl_Position.z;
                g_o.size += vec2(blur_rate * gl_in[0].gl_Position.z / window_size.x * 4,
                                                 blur_rate * gl_in[0].gl_Position.z / window_size.y * -4);

        }
        EmitVertex();
        EndPrimitive();
}

FRAGMENT WITH SHADOWS

#version 440

in GS_OUT {
        vec2 size;
        vec2 tex;
        vec4 col;
        vec4 data;
        vec4 data2;
        float tid;
} f;

uniform vec2 window_size;

const vec2 size = abs(f.size) * window_size / 2;
const vec2 uv = f.tex * size;

out vec4 color;

float circle_alpha(in vec2 pos, in float r) {
        return 1.f - length(uv - pos) / r;
}

float gradient_transform(in float val) {
        //const float pi = 3.14159265f;
        //const float result = sin(clamp(val, 0, 1) * pi - pi / 2) / 2 + 0.5f;
        //return result;
        return 1 - sqrt(1 - val);
}

void main() {
        const vec2 real_size = abs(f.data2.xy) * window_size / 2;
        const vec2 radius = size - real_size;
        const vec2 outer_radius = radius / 2;

        if (f.tid == 0.f) {
                color = f.col;
                float val = 1.f;
                if (uv.x < outer_radius.x) val = 0.f;
                if (uv.y < outer_radius.y) val = 0.f;
                if (uv.x > outer_radius.x + real_size.x) val = 0.f;
                if (uv.y > outer_radius.y + real_size.y) val = 0.f;
                color.w = val;
        } else if (f.tid == 1.f) {
                float val = 1.f;
                if (uv.x < radius.x) {
                        if (uv.y < radius.y) {
                                val = clamp(circle_alpha(radius, radius.x), 0, 1);
                        } else if (uv.y > real_size.y) {
                                val = clamp(circle_alpha(vec2(radius.x, real_size.y), radius.x), 0, 1);
                        } else {
                                val = uv.x / radius.x;
                        }
                } else if (uv.x > real_size.x) {
                        if (uv.y < radius.y) {
                                val = clamp(circle_alpha(vec2(real_size.x, radius.y), radius.x), 0, 1);
                        } else if (uv.y > real_size.y) {
                                val = clamp(circle_alpha(vec2(real_size.x, real_size.y), radius.x), 0, 1);
                        } else {
                                val = abs(real_size.x + radius.x - uv.x) / radius.x;
                        }
                } else if (uv.y < radius.y) {
                        val = uv.y / radius.y;
                } else if (uv.y > real_size.y) {
                        val = abs(real_size.y + radius.y - uv.y) / radius.y;
                }
                color = f.col;
                color.w *= gradient_transform(val);
        }
}

*/
