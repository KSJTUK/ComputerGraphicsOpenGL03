#version 460 core

layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in vec3 fragmentPositions[];
out vec3 fragPosition;

in vec2 texCoords[];
out vec2 texCoord;

in vec3 norms[];
out vec3 vNormal;

uniform vec3 centerPosition;
uniform vec3 radius;

void GenerateLine(int index)
{
	gl_Position = gl_in[index].gl_Position;
	EmitVertex();

	gl_Position = gl_in[index].gl_Position + vec4(norms[index], 0.0f);
	EmitVertex();
	EndPrimitive();
}

void main(void)
{
	for (int i = 0; i < gl_in.length(); ++i) { 
		fragPosition = fragmentPositions[i];
		texCoord = texCoords[i];
		vNormal = norms[i];
	}

	GenerateLine(0);
	GenerateLine(1);
	GenerateLine(2);
}