#version 460 core

// vertices = 3 -> �ﰢ�� ��ġ�� ��� 
// ������ ���� 3���� ����
layout (vertices = 3) out;

in vec3 fragPosition[];
out vec3 fragPositions[];

in vec3 norms[];
out vec3 normals[];

in vec2 texCoords[];
out vec2 textureCoords[];

uniform vec3 viewPosForDynamicTessel;
uniform float distanceEnavleTessel;

void main()
{
	// �ﰢ�� ��ġ���� �ܺ� ������ ���� ������ �׼����̼� ������ ���� (�ִ� 5)
	gl_TessLevelOuter[0] = 6;
	gl_TessLevelOuter[1] = 6;
	gl_TessLevelOuter[2] = 6;

	// �ﰢ�� ��ġ ���� ������ ���� ������ �׼����̼� ������ ���� (���������� �ִ� 5)
	gl_TessLevelInner[0] = 3;

	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
	textureCoords[gl_InvocationID] = texCoords[gl_InvocationID];
	normals[gl_InvocationID] = norms[gl_InvocationID];
	fragPositions[gl_InvocationID] = fragPosition[gl_InvocationID];
}