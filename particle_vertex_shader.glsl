#version 460 core

layout(location=0) vec3 in_position;
layout(location=1) vec4 in_particleColor;
layout(location=2) vec2 in_tex;

out vec4 vs_out_color;
out vec2 vs_out_tex;

uniform mat4 projectionMat;

void main(void)
{
	gl_Position = projectionMat * vec4(in_position, 0.0f);
	vs_out_color = in_particleColor;
	vs_out_tex = in_tex;
}