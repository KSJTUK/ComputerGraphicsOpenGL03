#version 460 core
//--- in_Position: attribute index 0
//--- in_Color: attribute index 1

layout (location = 0) in vec3 in_Position; //--- ��ġ ����: attribute position 0
layout (location = 1) in vec2 in_Texture; //--- �ؽ�ó ����: attribute position 1
layout (location = 2) in vec3 in_Normal; //--- ���� ��� ����: attribute position 2

out vec2 texCoord;

uniform mat4 perspective;
uniform mat4 view;
uniform mat4 transform;

void main(void)
{
	perspective;
	view;
	texCoord = in_Texture;

	gl_Position = transform * vec4(in_Position, 1.0f);
}