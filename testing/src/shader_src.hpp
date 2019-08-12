#pragma once

constexpr char s_vert_src[] = R"(
#version 330 core

layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 tex;

uniform vec2 mouse_pos;
uniform vec2 screen_size;
uniform vec2 cam_pos;
uniform float time;

out vec2 v_tex;

void main() {
    v_tex = tex;
    gl_Position = vec4((2 * pos - 2 * cam_pos) / screen_size - 1, 0, 1);
}
)";

constexpr char s_frag_src[] = R"(
#version 330 core

in vec2 v_tex;

out vec4 color;

// float rect(in vec2 pos, in vec2 size, in float radius = 1) {
//	if (radius > size.x) radius = size.x;
//	if (radius > size.y) radius = size.y;
//	return clamp((1 - length(max(abs(uv - pos) - size + radius, 0)) / radius) * radius, 0, 1);
// }

void main() {
    color = vec4(1, 0.5, 0.5, 1);
}
)";
