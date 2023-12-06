#version 460 core

layout(location=0) in vec3 in_position;
layout(location=1) in vec2 in_tex;
layout(location=2) in vec4 in_particleColor;

out vec4 vs_out_color;
out vec2 vs_out_tex;

void main(void)
{
	gl_Position = vec4(in_position, 1.0f);
	vs_out_color = in_particleColor;
	vs_out_tex = in_tex;
}