#version 460 core

layout (location = 0) in vec3 in_Position; //--- ��ġ ����: attribute position 0
layout (location = 1) in vec2 in_Texture; //--- �ؽ�ó ����: attribute position 1
layout (location = 2) in vec3 in_Normal; //--- ���� ��� ����: attribute position 2

out vec2 vs_out_tex;
out vec3 vs_out_normal;

uniform mat4 viewMat;
uniform mat4 perspectiveMat;

void main(void)
{
	gl_Position = perspectiveMat * viewMat * vec4(in_Position, 1.0f);
	vs_out_tex = in_Texture;
	vs_out_normal = in_Normal;
}