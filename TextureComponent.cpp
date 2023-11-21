#include "pch.h"
#include "TextureComponent.h"

TextureComponent::TextureComponent(const std::string& textureFilePath) {
	m_filePath = textureFilePath;
	CreateTexture();
}

TextureComponent::TextureComponent(const std::string& textureFilePath, bool flipImageOnLoad) {
	m_filePath = textureFilePath;
	CreateTexture(flipImageOnLoad);
}

TextureComponent::~TextureComponent() { }

void TextureComponent::SetTextureDefaultOption() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void TextureComponent::CreateTexture(bool flipImage) {
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	stbi_set_flip_vertically_on_load(flipImage);

	unsigned char* imageData = stbi_load(m_filePath.c_str(), &m_width, &m_height, &m_nrChannels, 0);
	assert(imageData);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(imageData);
}

uint32 TextureComponent::GetTextureID() const {
	return m_textureID;
}