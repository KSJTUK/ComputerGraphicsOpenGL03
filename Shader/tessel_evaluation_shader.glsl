#version 460 core

// ��ġ�� ������ �ﰢ��, ccw���ķ� ����
// �߰��� ������ �����ϴ� ������ �����ϴ� ���� (equal spacing -> ���� �������� ����)
layout (triangles, equal_spacing, ccw) in;

// �׼����̼� ���̴����� ��� input�� �迭 ���¿����� -> ��ġ ���·� �Է��� ���� ����
in vec3 fragPositions[];
out vec3 fragmentPositions;

in vec2 textureCoords[];
out vec2 texCoords;

in vec3 normals[];
out vec3 norms;


void main(void)
{
	// ������ ��ġ�� ����ġ �޾ƿ���
	float u = gl_TessCoord.x;
	float v = gl_TessCoord.y;
	float w = gl_TessCoord.z;

	// ������ ��ġ�� ��Ʈ�� ����Ʈ ����
	vec4 p0 = gl_in[0].gl_Position;
	vec4 p1 = gl_in[1].gl_Position;
	vec4 p2 = gl_in[2].gl_Position;

	// ��Ʈ�� ����Ʈ�� ����ġ�� ���ϰ� ���� ������ ���� ���ο� ���� ����
	vec4 p = p0 * u + p1 * v + p2 * w;

	// �����׸�Ʈ ��ġ, �ؽ���UV, ��� ���͵� ���Ӱ� ������ ������ ���� ���� ����
	vec2 textureUV = u * textureCoords[0]  + v * textureCoords[1] + w * textureCoords[2];
	vec3 normalVec = u * normals[0] + v * normals[1] + w * normals[2];
	vec3 fragPos = u * fragPositions[0] + v * fragPositions[1] + w * fragPositions[2];

	// ���� ��ġ�� ����
	gl_Position = p;

	// ���� �ؽ���UV, ���, �����׸�Ʈ ��ġ ����
	texCoords = textureUV;
	norms = normalVec;
	fragmentPositions = fragPos;
}