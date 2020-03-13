#pragma once

static constexpr const char *const vertSrc = R"(
#version 440

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec2 siz;
layout (location = 3) in vec4 col;
layout (location = 4) in vec4 data;

uniform ivec2 size;

out vec2 v_tex;
out vec4 v_col;

void main() {
	v_tex = tex, v_col = col / 255;
    v_tex.y = 1.f - v_tex.y;
    vec2 p = pos / size * 2 - 1;
    p.y *= -1;
	gl_Position = vec4(p, 0, 1);
}
)";

static constexpr const char *const fragSrc = R"(
#version 440

in vec2 v_tex;
in vec4 v_col;
uniform sampler2D tex;

out vec4 color;

float median(float r, float g, float b) {
    return max(min(r, g), min(max(r, g), b));
}

void main() {
    vec3 texVal = texture(tex, v_tex).rgb;
    ivec2 sz = textureSize(tex, 0).xy;
    float dx = dFdx(v_tex.x) * sz.x; 
    float dy = dFdy(v_tex.y) * sz.y;
    float toPixels = 8.0 * inversesqrt(dx * dx + dy * dy);
    float sigDist = median(texVal.r, texVal.g, texVal.b);
    float w = fwidth(sigDist);
    float opacity = smoothstep(0.5 - w, 0.5 + w, sigDist);

	color = v_col;
    color.w *= clamp(opacity, 0.2f, 1.f);
}
)";
