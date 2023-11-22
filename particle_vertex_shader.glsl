#version 460 core

layout(location = 0) in vec3 in_vertex;
layout(location = 1) in vec2 in_tex;

uniform vec3 objectColor;

out vec3 fragColor;

void main(void)
{
	gl_Position = vec4(in_vertex, 0.0f);
	fragColor = objectColor;
}