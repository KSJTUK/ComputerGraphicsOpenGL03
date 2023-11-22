#version 460 core

layout(points) in;
layout(line_strip, max_vertices = 360) out;

in vec3 in_vertex[];
in vec3 in_color[];
in float in_radiuse[];

out vec3 out_color;
out float out_radius;

void main(void)
{
	float angle = 0.0f;
	for (int i = 0; i < 360.f; ++i) {
		
	}
}