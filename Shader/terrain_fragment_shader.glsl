#version 460 core

in float Height;
out vec4 fragColor;

void main(void)
{
	float h = (Height + 64.0f)/128.0f;
	fragColor = vec4(h, h, h, 1.0f);
}