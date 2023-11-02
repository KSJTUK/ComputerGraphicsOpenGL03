#version 330 core
//--- in_Position: attribute index 0
//--- in_Color: attribute index 1

layout (location = 0) in vec3 in_Position; //--- ��ġ ����: attribute position 0
layout (location = 1) in vec3 in_Color; //--- �÷� ����: attribute position 1

uniform mat4 perspectiveMat;
uniform mat4 viewMat;
uniform mat4 modelTransform;

out vec3 out_Color; //--- �����׸�Ʈ ���̴����� ����

void main(void)
{
	gl_Position = perspectiveMat * viewMat * modelTransform * vec4(in_Position, 1.0f);
	out_Color = in_Color;
}