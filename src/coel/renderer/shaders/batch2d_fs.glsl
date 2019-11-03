R""(
#version 440

in GS_OUT {
    vec2 size;
	vec2 tex;
    vec4 col;
    float mat;
    vec4 data1, data2;
} f;

uniform vec2 window_size;

float ellipse(in vec2 p, in vec2 r) {
	return 2 * length(r) * (1 - length(p / r));
}

float line(in vec2 pos, in vec2 a, in vec2 b, in float radius) {
    vec2 ab = b - a;
    float t = clamp(dot(pos - a, ab) / dot(ab, ab), 0, 1);
    return radius - length(pos - a - t * ab);
}


out vec4 color;

void main() {
	const vec2 size = abs(f.size);
	const vec2 uv = size * f.tex;
    color = f.col;
	if (f.mat == 2.f) {
		color.w *= clamp(ellipse(uv - size / 2, size / 2), 0, 1);
	} else if (f.mat == 3.f) {
		const vec2 offset = vec2(f.data1.x / 2);
		color.w *= line(uv, vec2(0), size, f.data1.x);
	}
}
)""
