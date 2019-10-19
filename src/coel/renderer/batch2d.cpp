#include "../../coel.hpp"
#include <glad/glad.h>

namespace coel { namespace renderer { namespace batch2d {
    struct Sprite {
        math::Vec2 pos, size;
        math::Color col;
        float tid;
    };

    static constexpr unsigned int s_sprite_max = 100000, s_vbuffer_size = sizeof(Sprite) * s_sprite_max,
                                  s_ibuffer_size = 6 * s_sprite_max;
    static unsigned int s_vao_id, s_vbo_id, s_ibo_id;
    static unsigned short s_indices[s_ibuffer_size];
    static unsigned int s_sprite_count = 0;
    static Sprite *s_vbuffer_pointer;
    static unsigned int s_viewport_width, s_viewport_height;
    static math::Color s_fill_color = {255, 0, 255, 255};

    static Shader s_shader;
    static constexpr char *const s_vertex_shader_source = R"(
#version 440

layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 size;
layout(location = 2) in vec4 col;
layout(location = 3) in float tid;

out VS_OUT {
	vec2 size;
	vec4 col;
	float tid;
} v;

void main() {
	v.size = size;
    v.col = col / 255;
    v.tid = tid;

	gl_Position = vec4(pos, 0, 1);
}
)",
                                 *const s_geometry_shader_source = R"(
#version 440

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in VS_OUT {
	vec2 size;
	vec4 col;
	float tid;
} g_i[];

out GS_OUT {
	vec2 size;
	vec4 col;
	float tid;
} g_o;

void main() {
	gl_Position = gl_in[0].gl_Position + vec4(0, 0, 0, 0);
	g_o.size = g_i[0].size;
	g_o.col = g_i[0].col;
	g_o.tid = g_i[0].tid;
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(g_i[0].size.x, 0, 0, 0);
	g_o.size = g_i[0].size;
	g_o.col = g_i[0].col;
	g_o.tid = g_i[0].tid;
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(0, g_i[0].size.y, 0, 0);
	g_o.size = g_i[0].size;
	g_o.col = g_i[0].col;
	g_o.tid = g_i[0].tid;
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(g_i[0].size.x, g_i[0].size.y, 0, 0);
	g_o.size = g_i[0].size;
	g_o.col = g_i[0].col;
	g_o.tid = g_i[0].tid;
	EmitVertex();
	EndPrimitive();
}
)",
                                 *const s_fragment_shader_source = R"(
#version 440

in GS_OUT {
	vec2 size;
	vec4 col;
	float tid;
} f;

out vec4 color;

void main() {
	color = f.col;
}
)";

    void init(const unsigned int width, const unsigned int height) {
        resize(width, height);

        glGenVertexArrays(1, &s_vao_id);
        glBindVertexArray(s_vao_id);

        glGenBuffers(1, &s_vbo_id);
        glBindBuffer(GL_ARRAY_BUFFER, s_vbo_id);
        glBufferData(GL_ARRAY_BUFFER, s_vbuffer_size, nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Sprite), (const void *)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Sprite), (const void *)8);
        glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Sprite), (const void *)16);
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Sprite), (const void *)20);

        glGenBuffers(1, &s_ibo_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_ibo_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(s_indices), s_indices, GL_STATIC_DRAW);

        s_vbuffer_pointer = reinterpret_cast<Sprite *>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

        s_shader = shader::create(ShaderType::Vertex, s_vertex_shader_source, ShaderType::Geometry, s_geometry_shader_source,
                                  ShaderType::Fragment, s_fragment_shader_source);
    }

    void resize(const unsigned int width, const unsigned int height) { s_viewport_width = width, s_viewport_height = height; }

    void fill_color(const math::Color &color) { s_fill_color = color; }

    void fill_rect(const float pos_x, const float pos_y, const float size_x, const float size_y) {
        const float px = 2.f * pos_x / s_viewport_width - 1, py = -2.f * pos_y / s_viewport_height + 1,
                    sx = 2.f * size_x / s_viewport_width, sy = -2.f * size_y / s_viewport_height;

        s_vbuffer_pointer->pos.x = px;
        s_vbuffer_pointer->pos.y = py;
        s_vbuffer_pointer->size.x = sx;
        s_vbuffer_pointer->size.y = sy;
        s_vbuffer_pointer->tid = -1.f;
        s_vbuffer_pointer->col = s_fill_color;
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
