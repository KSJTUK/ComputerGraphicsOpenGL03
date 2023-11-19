#version 460 core

// 패치의 종류는 삼각형, ccw정렬로 설정
// 중간의 변수는 보간하는 간격을 조정하는 변수 (equal spacing -> 일정 간격으로 보간)
layout (triangles, equal_spacing, ccw) in;

in vec3 fragPositions[];
out vec3 fragPosition;

in vec2 textureCoords[];
out vec2 texCoord;

in vec3 normals[];
out vec3 vNormal;


void main(void)
{
	float u = gl_TessCoord.x;
	float v = gl_TessCoord.y;
	float w = gl_TessCoord.z;

	vec4 p0 = gl_in[0].gl_Position;
	vec4 p1 = gl_in[1].gl_Position;
	vec4 p2 = gl_in[2].gl_Position;

	vec4 p = p0 * u + p1 * v + p2 * w;

	vec2 textureUV = u * textureCoords[0]  + v * textureCoords[1] + w * textureCoords[2];

	vec3 normalVec = u * normals[0] + v * normals[1] + w * normals[2];

	vec3 fragPos = u * fragPositions[0] + v * fragPositions[1] + w * fragPositions[2];

	gl_Position = p;

	texCoord = textureUV;
	vNormal = normalVec;
	fragPosition = fragPos;
}