#version 460 core

uniform vec3 in_vertex;
uniform vec3 in_color;

uniform float in_radius;

out vec3 out_vertex;
out vec3 out_color;
out float out_radius;

void main(void)
{
	out_vertex = in_vertex;
	out_color = in_color;
	out_radius = in_radius;
	gl_Position = vec4(in_vertex, 0.0f);
}