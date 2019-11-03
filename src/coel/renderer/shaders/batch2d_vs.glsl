R""(
#version 440

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 size;
layout(location = 2) in vec4 col;
layout(location = 3) in float mat;
layout(location = 4) in vec4 data1;
layout(location = 5) in vec4 data2;

uniform vec2 window_size;

out VS_OUT {
	vec2 size;
	vec4 col;
	float mat;
	vec4 data1, data2;
} v;

void main() {
    v.size = size;
    v.col = col / 255;
    v.mat = mat;
    v.data1 = data1;
    v.data2 = data2;
	gl_Position = vec4(
        pos.x *  2 / window_size.x - 1, 
        pos.y * -2 / window_size.y + 1, 
        pos.z / 1000, 1);
}
)""
