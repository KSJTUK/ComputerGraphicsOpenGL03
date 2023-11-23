#version 460 core

layout (vertices=3) out;

// varying input from vertex shader
in vec2 vs_out_tex[];
in vec3 vs_out_normal[];
// varying output to evaluation shader
out vec2 tcs_out_tex[];
out vec3 tcs_out_normal[];

const int tessLevel = 16;

void main()
{
    // ----------------------------------------------------------------------
    // pass attributes through
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    tcs_out_tex[gl_InvocationID] = vs_out_tex[gl_InvocationID];
    tcs_out_normal[gl_InvocationID] = vs_out_normal[gl_InvocationID];

    // ----------------------------------------------------------------------
    // invocation zero controls tessellation levels for the entire patch
    if (gl_InvocationID == 0)
    {
        gl_TessLevelOuter[0] = tessLevel;
        gl_TessLevelOuter[1] = tessLevel;
        gl_TessLevelOuter[2] = tessLevel;

        gl_TessLevelInner[0] = tessLevel;
    }
}