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

void set_all_values() {
    g_o.size = g_i[0].size;
    g_o.col = g_i[0].col;
    g_o.mat = g_i[0].mat;
    g_o.data1 = g_i[0].data1;
    g_o.data2 = g_i[0].data2;
}

void main() {
	const vec2 border_radius = vec2(g_i[0].data1.x * 2) / window_size;
	
    gl_Position = gl_in[0].gl_Position + vec4(0, 0, 0, 0);
    g_o.tex = vec2(0, 0);
	set_all_values();

	if (g_o.mat < 2.5) {
	} else if (g_o.mat < 3.5f) {
		vec2 mult = vec2(1.f);
		if (g_o.size.x < 0.f) mult.x = -1.f;
		if (g_o.size.y > 0.f) mult.y = -1.f;
		g_o.size.x += mult.x * g_o.data1.x * 2;
		g_o.size.y += mult.y * g_o.data1.x * 2;
		gl_Position.x -= mult.x * border_radius.x;
		gl_Position.y -= mult.y * border_radius.y;
	}
    EmitVertex();
    
    gl_Position = gl_in[0].gl_Position + vec4(0, g_i[0].size.y / window_size.y * -2, 0, 0);
    g_o.tex = vec2(0, 1);
	set_all_values();

	if (g_o.mat < 2.5) {
	} else if (g_o.mat < 3.5f) {
		vec2 mult = vec2(1.f);
		if (g_o.size.x < 0.f) mult.x = -1.f;
		if (g_o.size.y > 0.f) mult.y = -1.f;
		g_o.size.x += mult.x * g_o.data1.x * 2;
		g_o.size.y += mult.y * g_o.data1.x * 2;
		gl_Position.x -= mult.x * border_radius.x;
		gl_Position.y += mult.y * border_radius.y;
	}
    EmitVertex();
    
    gl_Position = gl_in[0].gl_Position + vec4(g_i[0].size.x / window_size.x * 2, 0, 0, 0);
    g_o.tex = vec2(1, 0);
	set_all_values();
	
	if (g_o.mat < 2.5) {
	} else if (g_o.mat < 3.5f) {
		vec2 mult = vec2(1.f);
		if (g_o.size.x < 0.f) mult.x = -1.f;
		if (g_o.size.y > 0.f) mult.y = -1.f;
		g_o.size.x += mult.x * g_o.data1.x * 2;
		g_o.size.y += mult.y * g_o.data1.x * 2;
		gl_Position.x += mult.x * border_radius.x;
		gl_Position.y -= mult.y * border_radius.y;
	}
    EmitVertex();
    
    gl_Position = gl_in[0].gl_Position + vec4(g_i[0].size.x / window_size.x * 2, g_i[0].size.y / window_size.y * -2, 0, 0);
    g_o.tex = vec2(1, 1);
	set_all_values();
	
	if (g_o.mat < 2.5) {
	} else if (g_o.mat < 3.5f) {
		vec2 mult = vec2(1.f);
		if (g_o.size.x < 0.f) mult.x = -1.f;
		if (g_o.size.y > 0.f) mult.y = -1.f;
		g_o.size.x += mult.x * g_o.data1.x * 2;
		g_o.size.y += mult.y * g_o.data1.x * 2;
		gl_Position.x += mult.x * border_radius.x;
		gl_Position.y += mult.y * border_radius.y;
	}
    EmitVertex();
    
    EndPrimitive();
}
)""
