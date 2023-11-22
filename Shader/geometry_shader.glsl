#version 460 core

layout (triangles) in;
layout (points, max_vertices = 3) out;

in vec3 fragmentPositions[];
out vec3 fragPosition;

in vec2 texCoords[];
out vec2 texCoord;

in vec3 norms[];
out vec3 vNormal;

void main(void)
{
	for (int i = 0; i < gl_in.length(); ++i) { 
		gl_Position = gl_in[i].gl_Position;

		fragPosition = fragmentPositions[i];
		texCoord = texCoords[i];
		vNormal = norms[i];

		EmitVertex();
		EndPrimitive();
	}
}