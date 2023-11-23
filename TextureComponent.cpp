#include "pch.h"
#include "TextureComponent.h"
#define STB_IMAGE_IMPLEMENTATION

TextureComponent::TextureComponent(const std::string& textureFilePath, int channel) {
	m_alphaChannel = channel;
	m_filePath = textureFilePath;
	CreateTexture();
}

TextureComponent::TextureComponent(const std::string& textureFilePath, int channel, bool flipImageOnLoad) {
	m_alphaChannel = channel;
	m_filePath = textureFilePath;
	CreateTexture(flipImageOnLoad);
}

TextureComponent::~TextureComponent() { }

void TextureComponent::SetTextureDefaultOption() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void TextureComponent::CreateTexture(bool flipImage) {

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	SetTextureDefaultOption();

	stbi_set_flip_vertically_on_load(flipImage);

	unsigned char* imageData = stbi_load(m_filePath.c_str(), &m_width, &m_height, &m_nrChannels, 0);
	if (imageData == NULL) {
		std::cout << "Cannot load image" << std::endl;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, m_alphaChannel, m_width, m_height, 0, m_alphaChannel, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(imageData);
}

uint32 TextureComponent::GetTextureID() const {
	return m_textureID;
}

glm::ivec3 TextureComponent::GetTextureInfo() const {
	return glm::ivec3{ m_width, m_height, m_nrChannels };
}
