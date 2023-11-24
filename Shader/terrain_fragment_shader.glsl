#version 460 core

in float height;
out vec4 fragColor;

void main(void)
{
	float heightColor = (height + 64.0f) / 128.0f;
	fragColor = vec4(heightColor, heightColor, heightColor, 1.0f);
}