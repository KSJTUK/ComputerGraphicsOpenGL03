#version 460 core

// ��ġ�� �簢������ ����
layout (vertices=4) out;

// ���� ���̴��� ���� �ؽ���, ��� ������ �޾ƿ���
in vec2 vs_out_tex[];
in vec3 vs_out_normal[];
in vec3 vs_out_fragPosition[];

// �׼����̼� �� TES ���̴��� ������ ����
out vec2 tcs_out_tex[];
out vec3 tcs_out_normal[];
out vec3 tcs_out_fragPosition[];

// �ּ� �׼����̼� ������ �ִ� �׼����̼� ������ ����
const int minTesselLevel = 2;
const int maxTesselLevel = 32;

// �ּ� �׼����̼� ������ �ִ� �׼����̼� ������ ������ �Ÿ� ����
// �ּҰŸ� -> �ִ� �׼����̼� ����, �ִ�Ÿ� -> �ּ� �׼����̼� ����
const float minDist = 20;
const float maxDist = 800;

const int tessLevel = 64;

void main()
{
    // ���� ���̴��� ������ ����
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    tcs_out_tex[gl_InvocationID] = vs_out_tex[gl_InvocationID];
    tcs_out_normal[gl_InvocationID] = vs_out_normal[gl_InvocationID];
    tcs_out_fragPosition[gl_InvocationID] = vs_out_fragPosition[gl_InvocationID];

    if (gl_InvocationID == 0) {
        // ��Ʈ�� ����Ʈ���� �޾ƿ���
        vec4 p00 = gl_in[0].gl_Position;
        vec4 p01 = gl_in[1].gl_Position;
        vec4 p10 = gl_in[2].gl_Position;
        vec4 p11 = gl_in[3].gl_Position;

        // ī�޶� �������� ������ ��Ʈ�� ����Ʈ���� z���� �Ÿ��� ���Ͽ�
        // ������ ���������� �Ÿ� ������ ���� (0~1)���� �� clamp�� ����� ���� ������ ������ �ʵ�����
        float distance00 = clamp((abs(p00.z) - minDist) / (maxDist - minDist), 0.0, 1.0 );
        float distance01 = clamp((abs(p01.z) - minDist) / (maxDist - minDist), 0.0, 1.0 );
        float distance10 = clamp((abs(p10.z) - minDist) / (maxDist - minDist), 0.0, 1.0 );
        float distance11 = clamp((abs(p11.z) - minDist) / (maxDist - minDist), 0.0, 1.0 );

        // �׼����̼� ������ �Ÿ� ������ ���� ������
        float tessLevel0 = mix(maxTesselLevel, minTesselLevel, min(distance10, distance00) );
        float tessLevel1 = mix(maxTesselLevel, minTesselLevel, min(distance00, distance01) );
        float tessLevel2 = mix(maxTesselLevel, minTesselLevel, min(distance01, distance11) );
        float tessLevel3 = mix(maxTesselLevel, minTesselLevel, min(distance11, distance10) );

        // �׼����̼� ���� ����
        gl_TessLevelOuter[0] = tessLevel0;
        gl_TessLevelOuter[1] = tessLevel1;
        gl_TessLevelOuter[2] = tessLevel2;
        gl_TessLevelOuter[3] = tessLevel3;

        // ���� �׼����̼� ������ �� �������� �׼����̼� ������ �߿��� ū ������ �����
        gl_TessLevelInner[0] = max(tessLevel1, tessLevel3);
        gl_TessLevelInner[1] = max(tessLevel0, tessLevel2);
    }
}