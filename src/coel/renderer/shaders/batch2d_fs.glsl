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
uniform sampler2D text_sdf;

const vec2 size = abs(f.size);
const vec2 uv = size * f.tex;

float ellipse(in vec2 p, in vec2 r) {
	return length(r) * (1 - length((uv - p) / r));
}

float line(in vec2 a, in vec2 b, in float radius) {
    vec2 ab = b - a;
    float t = clamp(dot(uv - a, ab) / dot(ab, ab), 0, 1);
    return clamp(radius - length(uv - a - t * ab), 0.25, 0.75) * 2 - 0.5;
}

out vec4 color;

void main() {
    color = f.col;
    switch (int(f.mat + 0.5)) {
    case 2: // Circle
		color.w *= clamp(ellipse(size / 2, size / 2), 0, 1);
        break;
    case 3: // Line
		const vec2 offset = vec2(f.data1.x);
		color.w *= line(offset, size - offset, f.data1.x);
        break;
    case 4: // Text
        vec4 t = texture(text_sdf, f.tex / 512 * f.data2.xy + f.data1.xy / 512);
        color.w *= clamp((t.x - 0.0) * 1, 0, 1);
        break;
    }
}
)""
