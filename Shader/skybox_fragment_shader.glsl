#version 460 core

in vec3 texCoord;

out vec4 FragColor;

uniform samplerCube cubeMapTexture;
uniform vec3 ambient;

void main(void)
{
	FragColor = texture(cubeMapTexture, texCoord);
}