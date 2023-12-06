#version 460 core

layout (quads, fractional_odd_spacing, ccw) in;
//layout (quads, equal_spacing, ccw) in;

in vec2 tcs_out_tex[];
in vec3 tcs_out_normal[];
in vec3 tcs_out_fragPosition[];

out vec2 tes_out_tex;
out vec3 tes_out_normal;
out vec3 tes_out_fragPosition;

out float height;
out float heightFactor;

uniform sampler2D heightMap;
uniform mat4 perspectiveMat;

vec4 heightNormal = vec4(0.0f, 1.0f, 0.0f, 0.0f);

vec3 calcTessellationedNormal(vec3 cp0, vec3 cp1, vec3 cpNormal0, vec3 cpNormal1)
{
    vec3 dirVec = cp0 - cp1;
    vec3 addNormal = cpNormal0 + cpNormal1;
    vec3 normal = addNormal - (2 * (dot(addNormal, dirVec) / dot(dirVec, dirVec))) * dirVec;
    return normal;
}

vec4 calcPostition(float u, float v, float height)
{ 
    // ��Ʈ�� ����Ʈ
    vec4 p00 = gl_in[0].gl_Position;
    vec4 p01 = gl_in[1].gl_Position;
    vec4 p10 = gl_in[2].gl_Position;
    vec4 p11 = gl_in[3].gl_Position;

    // �簢���̹Ƿ� �� �������� ���������� ����� ���
    //vec4 uVec = p01 - p00;
    //vec4 vVec = p10 - p00;
    //vec4 normal = normalize( vec4(cross(uVec.xyz, vVec.xyz), 0) );


    vec4 p0 = (p01 - p00) * u + p00;
    vec4 p1 = (p11 - p10) * u + p10;
    return (p1 - p0) * v + p0 + heightNormal * height;
}

vec3 calcFragPos(float u, float v, float height)
{
    vec3 fp00 = tcs_out_fragPosition[0];
    vec3 fp01 = tcs_out_fragPosition[1];
    vec3 fp10 = tcs_out_fragPosition[2];
    vec3 fp11 = tcs_out_fragPosition[3];

    vec3 fp0 = (fp01 - fp00) * u + fp00;
    vec3 fp1 = (fp11 - fp10) * u + fp10;
    return (fp1 - fp0) * v + fp0 + vec3(heightNormal) * height;
}

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
    heightFactor = 64.0f;
    height = texture(heightMap, texCoord).x * heightFactor - heightFactor / 2.0f;

    vec4 p = calcPostition(u, v, height);
    tes_out_fragPosition = calcFragPos(u, v, height);

    gl_Position = perspectiveMat * p;

    tes_out_tex = texCoord;
    tes_out_normal = vec3(heightNormal);
}