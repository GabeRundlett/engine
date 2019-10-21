R""(
#version 440

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform vec2 window_size;

in VS_OUT {
	vec2 size;
	vec4 col;
	float mat;
	vec4 data1, data2;
} g_i[];

out GS_OUT {
    vec2 size;
	vec2 tex;
    vec4 col;
    float mat;
    vec4 data1, data2;
} g_o;

void main() {
    gl_Position = gl_in[0].gl_Position + vec4(0, 0, 0, 0);
    g_o.size = g_i[0].size;
    g_o.tex = vec2(0, 0);
    g_o.col = g_i[0].col;
    g_o.mat = g_i[0].mat;
    g_o.data1 = g_i[0].data1;
    g_o.data2 = g_i[0].data2;
    EmitVertex();
    
    gl_Position = gl_in[0].gl_Position + vec4(0, g_i[0].size.y / window_size.y * -2, 0, 0);
    g_o.size = g_i[0].size;
    g_o.tex = vec2(0, 1);
    g_o.col = g_i[0].col;
    g_o.mat = g_i[0].mat;
    g_o.data1 = g_i[0].data1;
    g_o.data2 = g_i[0].data2;
    EmitVertex();
    
    gl_Position = gl_in[0].gl_Position + vec4(g_i[0].size.x / window_size.x * 2, 0, 0, 0);
    g_o.size = g_i[0].size;
    g_o.tex = vec2(1, 0);
    g_o.col = g_i[0].col;
    g_o.mat = g_i[0].mat;
    g_o.data1 = g_i[0].data1;
    g_o.data2 = g_i[0].data2;
    EmitVertex();
    
    gl_Position = gl_in[0].gl_Position + vec4(g_i[0].size.x / window_size.x * 2, g_i[0].size.y / window_size.y * -2, 0, 0);
    g_o.size = g_i[0].size;
    g_o.tex = vec2(1, 1);
    g_o.col = g_i[0].col;
    g_o.mat = g_i[0].mat;
    g_o.data1 = g_i[0].data1;
    g_o.data2 = g_i[0].data2;
    EmitVertex();
    
    EndPrimitive();
}
)""