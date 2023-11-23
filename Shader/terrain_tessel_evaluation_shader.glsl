#version 460 core

layout (triangles, fractional_odd_spacing, ccw) in;

in vec2 tcs_out_tex[];
in vec3 tcs_out_normal[];

out float Height;

uniform sampler2D heightMap;

void main()
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
	vec4 p = u * p0 + v * p1 + w * p2;
    vec2 texCoord = u * tcs_out_tex[0] + v * tcs_out_tex[1] + w * tcs_out_tex[2];


    Height = texture(heightMap, texCoord).y * 128.0f - 64.0f;

    vec3 normal = u * tcs_out_normal[0] + v * tcs_out_normal[1] + w * tcs_out_normal[2];

	// ��ֿ� ������ ���̸� ���ؼ� ������ ���̸�ŭ �ű�
    p += vec4(normal * Height, 0.f);

    gl_Position = p;
}
