#version 460 core

layout (quads, fractional_odd_spacing, ccw) in;

in vec2 tcs_out_tex[];
in vec3 tcs_out_normal[];

out float height;

uniform sampler2D heightMap;
uniform mat4 perspectiveMat;

void main()
{
    // ����ġ (���� ������ �����)�� �޾ƿ�
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;

    // ��Ʈ�� ����Ʈ���� �ؽ��� ��ǥ��
    vec2 t00 = tcs_out_tex[0];
    vec2 t01 = tcs_out_tex[1];
    vec2 t10 = tcs_out_tex[2];
    vec2 t11 = tcs_out_tex[3];

    // ���� ������ ������Ƽ���� �ؽ��� ��ǥ�� ���������Ͽ� �����
    vec2 t0 = (t01 - t00) * u + t00;
    vec2 t1 = (t11 - t10) * u + t10;
    vec2 texCoord = (t1 - t0) * v + t0;

    // ����Ʈ �ʿ��� �ؽ��� ������ �޾ƿ�
    height = texture(heightMap, texCoord).y * 128.0f - 64.0f;

    // ��Ʈ�� ����Ʈ
    vec4 p00 = gl_in[0].gl_Position;
    vec4 p01 = gl_in[1].gl_Position;
    vec4 p10 = gl_in[2].gl_Position;
    vec4 p11 = gl_in[3].gl_Position;

    // �簢���̹Ƿ� �� �������� ���������� ����� ���
    vec4 uVec = p01 - p00;
    vec4 vVec = p10 - p00;
    vec4 normal = normalize( vec4(cross(uVec.xyz, vVec.xyz), 0) );


    vec4 p0 = (p01 - p00) * u + p00;
    vec4 p1 = (p11 - p10) * u + p10;
    vec4 p = (p1 - p0) * v + p0 + normal * height;

    gl_Position = perspectiveMat * p;
}