#version 460 core

layout(location=0) in vec3 in_Position;

uniform mat4 perspectiveMat;
uniform mat4 viewMat;

out vec3 texCoord;

void main(void) 
{
	texCoord = in_Position;
	vec4 position = perspectiveMat * viewMat * vec4(in_Position, 1.0f);
	gl_Position = position.xyww;
}