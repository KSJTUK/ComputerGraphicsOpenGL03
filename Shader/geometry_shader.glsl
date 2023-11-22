#version 460 core

layout (points) in;
layout (line_strip, max_vertices = 3) out;

in vec4 vs_out_color[];
in vec2 vs_out_tex[];

out vec4 gs_out_color;
out vec2 gs_out_tex;

void main(void)
{
	for (int i = 0; i < gl_in.length(); ++i) { 
		gl_Position = gl_in[i].gl_Position;

		gs_out_color = vs_out_color[i];
		gs_out_tex = vs_out_tex[i];

		EmitVertex();
		EndPrimitive();
	}
}