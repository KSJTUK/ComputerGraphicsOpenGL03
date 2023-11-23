#version 460 core

layout (location = 0) in vec3 in_Position; //--- ��ġ ����: attribute position 0
layout (location = 1) in vec2 in_Texture; //--- �ؽ�ó ����: attribute position 1
layout (location = 2) in vec3 in_Normal; //--- ���� ��� ����: attribute position 2

void main(void)
{
	gl_Position = vec4(in_Position, 1.0f);
}