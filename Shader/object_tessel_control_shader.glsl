#version 460 core

// vertices = 3 -> �ﰢ�� ��ġ�� ��� 
// ������ ���� 3���� ����
layout (vertices = 3) out;

in vec3 fragPosition[];
out vec3 fragPositions[];

in vec3 vNormal[];
out vec3 normals[];

in vec2 texCoord[];
out vec2 textureCoords[];

uniform vec3 viewPositionForDynamicTessel;

const int maxTesselLevel = 10;
const int minTesselLevel = 2;

const float maxTesselDist = 1.5f;
const float minTesselDist = 0.1f;

const int tesselLevel = 1;

void main()
{
	// �ﰢ�� ��ġ���� �ܺ� ������ ���� ������ �׼����̼� ������ ���� (�ִ� 5)
	gl_TessLevelOuter[0] = tesselLevel;
	gl_TessLevelOuter[1] = tesselLevel;
	gl_TessLevelOuter[2] = tesselLevel;

	// �ﰢ�� ��ġ ���� ������ ���� ������ �׼����̼� ������ ���� (���������� �ִ� 5)
	gl_TessLevelInner[0] = tesselLevel;

	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
	textureCoords[gl_InvocationID] = texCoord[gl_InvocationID];
	normals[gl_InvocationID] = vNormal[gl_InvocationID];
	fragPositions[gl_InvocationID] = fragPosition[gl_InvocationID];
}