#version 460 core

layout (vertices=4) out;

// varying input from vertex shader
in vec2 vs_out_tex[];
in vec3 vs_out_normal[];
// varying output to evaluation shader
out vec2 tcs_out_tex[];
out vec3 tcs_out_normal[];

const int minTesselLevel = 2;
const int maxTesselLevel = 32;

const float minDist = 20;
const float maxDist = 800;

const int tessLevel = 64;

void main()
{
    // ----------------------------------------------------------------------
    // pass attributes through
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    tcs_out_tex[gl_InvocationID] = vs_out_tex[gl_InvocationID];
    tcs_out_normal[gl_InvocationID] = vs_out_normal[gl_InvocationID];

    if (gl_InvocationID == 0) {
        // 만약 카메라와의 거리가 MAXDIST이상이면 보간 계수를 1로 MINDIST이하이면 계수를 0으로 하여 레벨을 선형보간함
        vec4 p00 = gl_in[0].gl_Position;
        vec4 p01 = gl_in[1].gl_Position;
        vec4 p10 = gl_in[2].gl_Position;
        vec4 p11 = gl_in[3].gl_Position;

        // "distance" from camera scaled between 0 and 1
        float distance00 = clamp((abs(p00.z) - minDist) / (maxDist - minDist), 0.0, 1.0 );
        float distance01 = clamp((abs(p01.z) - minDist) / (maxDist - minDist), 0.0, 1.0 );
        float distance10 = clamp((abs(p10.z) - minDist) / (maxDist - minDist), 0.0, 1.0 );
        float distance11 = clamp((abs(p11.z) - minDist) / (maxDist - minDist), 0.0, 1.0 );

        float tessLevel0 = mix(maxTesselLevel, minTesselLevel, min(distance10, distance00) );
        float tessLevel1 = mix(maxTesselLevel, minTesselLevel, min(distance00, distance01) );
        float tessLevel2 = mix(maxTesselLevel, minTesselLevel, min(distance01, distance11) );
        float tessLevel3 = mix(maxTesselLevel, minTesselLevel, min(distance11, distance10) );

        gl_TessLevelOuter[0] = tessLevel0;
        gl_TessLevelOuter[1] = tessLevel1;
        gl_TessLevelOuter[2] = tessLevel2;
        gl_TessLevelOuter[3] = tessLevel3;

        gl_TessLevelInner[0] = max(tessLevel1, tessLevel3);
        gl_TessLevelInner[1] = max(tessLevel0, tessLevel2);
    }
}