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

void text(inout vec4 col, int character) {
    const float thic = 0.1;
    switch (character) {
    case 30:
        break;
    case 31:
        break;
    case 32: // SPACE
        col.w *= 0.1f;
        break;
    case 33: // !
        col.w *= line(vec2(size.x * 0.5, size.y * 0.1), vec2(size.x * 0.5, size.y * 0.6), size.x * thic) +
                clamp(ellipse(vec2(size.x * 0.5, size.y * 0.8), vec2(size.x * thic * 1.5)), 0, 1);
        break;
    case 34: // "
        col.w *= line(vec2(size.x * 0.3, size.y * 0.1), vec2(size.x * 0.3, size.y * 0.3), size.x * thic) +
                line(vec2(size.x * 0.7, size.y * 0.1), vec2(size.x * 0.7, size.y * 0.3), size.x * thic);
        break;
    case 35: // #
        col.w *= line(vec2(size.x * 0.35, size.y * 0.1), vec2(size.x * 0.25, size.y * 0.9), size.x * thic) +
                line(vec2(size.x * 0.75, size.y * 0.1), vec2(size.x * 0.65, size.y * 0.9), size.x * thic) +
                line(vec2(size.x * 0.1, size.y * 0.3), vec2(size.x * 0.9, size.y * 0.3), size.x * thic) +
                line(vec2(size.x * 0.1, size.y * 0.7), vec2(size.x * 0.9, size.y * 0.7), size.x * thic);
        break;
    case 36: // $
        break;
    case 37: // %
        break;
    case 38: // &
        break;
    case 39: // ' 
        break;
    case 40: // (
        break;
    case 41: // )
        break;
    case 42: // *
        break;
    case 43: // +
        break;
    case 44: // ,
        break;
    case 45:
        break;
    case 46:
        break;
    case 47:
        break;
    case 48:
        break;
    case 49:
        break;
    case 50:
        break;
    case 51:
        break;
    case 52:
        break;
    case 53:
        break;
    case 54:
        break;
    case 55:
        break;
    case 56:
        break;
    case 57:
        break;
    case 58:
        break;
    case 59:
        break;
    }
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
        text(color, int(f.data1.x + 0.5));
        break;
    }
}
)""
