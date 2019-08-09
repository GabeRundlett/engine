#pragma once

constexpr char s_vert_src[] = R"(
#version 330 core

layout(location = 0) in vec2 pos; 
layout(location = 1) in vec3 tex;

out vec3 v_tex;

void main() {
    v_tex = tex;
    gl_Position = vec4(pos, 0, 1);
}

)";

constexpr char s_frag_src[] = R"(
#version 330 core

in vec3 v_tex;

uniform vec2 mouse_pos;
uniform vec2 screen_size;
uniform vec2 player_pos;
uniform float time;

out vec4 color;

vec2 uv = v_tex.xy * screen_size;

float rect(in vec2 pos, in vec2 size, in float radius = 1) {
	if (radius > size.x) radius = size.x;
	if (radius > size.y) radius = size.y;
	return clamp((1 - length(max(abs(uv - pos) - size + radius, 0)) / radius) * radius, 0, 1);
}

void main() {
    float val = rect(player_pos.xy, vec2(10, 10), 4);
    color = vec4(vec3(val), 1);
}
)";
