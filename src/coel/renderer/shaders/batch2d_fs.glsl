R""(
#version 440

in GS_OUT {
    vec2 size;
	vec2 tex;
    vec4 col;
    float mat;
    vec4 data1, data2;
} f;

out vec4 color;

void main() {
    color = f.col;
}
)""