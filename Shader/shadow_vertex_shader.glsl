#version 460 core
layout (location = 0) in vec3 in_Position;

uniform mat4 lightSpaceMat;
uniform mat4 transform;

void main()
{
    gl_Position = lightSpaceMat * transform * vec4(in_Position, 1.0);
}