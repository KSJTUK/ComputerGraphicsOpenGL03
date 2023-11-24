#include "pch.h"
#include "TextureComponent.h"

TextureComponent::TextureComponent() { }

TextureComponent::~TextureComponent() { }

void TextureComponent::LoadTexture(const std::string& textureFilePath, int channel, bool flipImageOnLoad) {
	TextureInfo texInfo{ };
	glGenTextures(1, &texInfo.id);
	glBindTexture(GL_TEXTURE_2D, texInfo.id);

	SetTextureDefaultOption();

	stbi_set_flip_vertically_on_load(flipImageOnLoad);

	unsigned char* imageData = stbi_load(textureFilePath.c_str(), &texInfo.width, &texInfo.height, &texInfo.nrChannel, 0);
	if (!imageData) {
		std::cerr << "texture file path wrong: not exist texture file, file name{ " << textureFilePath << " }";
		exit(EXIT_FAILURE);
	}
	std::cout << "texture file load success : file name{ " << textureFilePath << " }\n";

	glTexImage2D(GL_TEXTURE_2D, 0, channel, texInfo.width, texInfo.height, 0, channel, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(imageData);

	m_textures.push_back(texInfo);
}

void TextureComponent::BindingTexture(int textureIndex) {
	glActiveTexture(GL_TEXTURE0 + textureIndex);
	glBindTexture(GL_TEXTURE_2D, m_textures[textureIndex].id);
}

void TextureComponent::UnBindingTextures() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureComponent::SetTextureDefaultOption() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

uint32 TextureComponent::GetTextureID(int textureIndex) {
	return m_textures[textureIndex].id;
}

const TextureInfo& TextureComponent::GetTextureInfo(int textureIndex) const {
	return m_textures[textureIndex];
}
