#include "../../coel.hpp"
#include <glad/glad.h>

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
        glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Sprite), (const void *)28);
        glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(Sprite), (const void *)44);

        s_vbuffer_pointer = reinterpret_cast<Sprite *>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

        s_shader = shader::create(ShaderType::Vertex, s_vertex_shader_source, ShaderType::Geometry, s_geometry_shader_source,
                                  ShaderType::Fragment, s_fragment_shader_source);
        resize(width, height);
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

    void fill_line(const Line &e) {
        s_vbuffer_pointer->pos = {e.a.x, e.a.y, 0.f};
        s_vbuffer_pointer->size = e.b - e.a;
        s_vbuffer_pointer->col = s_fill_color;
        s_vbuffer_pointer->mat = 3.f;
        s_vbuffer_pointer->data1 = e.data1;
        s_vbuffer_pointer->data2 = e.data2;
        ++s_vbuffer_pointer;
        ++s_sprite_count;
        if (s_sprite_count > s_sprite_max) flush();
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
        gl_Position = gl_in[0].gl_Position + vec4(0, 0, 0, 0);
        g_o.size = g_i[0].size;
        g_o.tex = vec2(0, 0);
        g_o.col = g_i[0].col;
        g_o.data = g_i[0].data;
        g_o.tid = g_i[0].tid;
        if (g_o.tid == 0.f || g_o.tid == 1.f) {
                gl_Position += vec4(-blur_rate * gl_in[0].gl_Position.z / window_size.x *  2,
                                                        -blur_rate * gl_in[0].gl_Position.z / window_size.y * -2, 0, 0);
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
        gl_Position = gl_in[0].gl_Position + vec4(g_i[0].size.x, 0, 0, 0);
        g_o.size = g_i[0].size;
        g_o.tex = vec2(1, 0);
        g_o.col = g_i[0].col;
        g_o.data = g_i[0].data;
        g_o.tid = g_i[0].tid;

        if (g_o.tid == 0.f || g_o.tid == 1.f) {
                gl_Position += vec4( blur_rate * gl_in[0].gl_Position.z / window_size.x *  2,
                                                        -blur_rate * gl_in[0].gl_Position.z / window_size.y * -2, 0, 0);
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
        gl_Position = gl_in[0].gl_Position + vec4(0, g_i[0].size.y, 0, 0);
        g_o.size = g_i[0].size;
        g_o.tex = vec2(0, 1);
        g_o.col = g_i[0].col;
        g_o.data = g_i[0].data;
        g_o.tid = g_i[0].tid;
        if (g_o.tid == 0.f || g_o.tid == 1.f) {
                gl_Position += vec4(-blur_rate * gl_in[0].gl_Position.z / window_size.x *  2,
                                                         blur_rate * gl_in[0].gl_Position.z / window_size.y * -2, 0, 0);
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
        gl_Position = gl_in[0].gl_Position + vec4(g_i[0].size.x, g_i[0].size.y, 0, 0);
        g_o.size = g_i[0].size;
        g_o.tex = vec2(1, 1);
        g_o.col = g_i[0].col;
        g_o.data = g_i[0].data;
        g_o.tid = g_i[0].tid;
        if (g_o.tid == 0.f || g_o.tid == 1.f) {
                gl_Position += vec4(blur_rate * gl_in[0].gl_Position.z / window_size.x *  2,
                                                        blur_rate * gl_in[0].gl_Position.z / window_size.y * -2, 0, 0);
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
