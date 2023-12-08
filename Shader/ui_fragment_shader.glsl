#version 460 core

out vec4 FragColor;
in vec2 texCoord;
uniform sampler2D uiImage;

void main(void)
{
	FragColor = texture(uiImage, texCoord);
}