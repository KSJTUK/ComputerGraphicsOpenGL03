#include "pch.h"
#include "TextureComponent.h"

TextureComponent::TextureComponent() { }

TextureComponent::~TextureComponent() { }

void TextureComponent::LoadTexture(const std::string& textureFilePath, bool flipImageOnLoad) {
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

	int channel{ };
	switch (texInfo.nrChannel) {
	case 1:
		channel = GL_RED;
		break;
	case 2:
		break;
	case 3:
		channel = GL_RGB;
		break;
	case 4:
		channel = GL_RGBA;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, channel, texInfo.width, texInfo.height, 0, channel, GL_UNSIGNED_BYTE, (void*)imageData);
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

CubeMapTexture::CubeMapTexture() { }

CubeMapTexture::~CubeMapTexture() { }

void CubeMapTexture::SetCubeMapTextureOption() {
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void CubeMapTexture::LoadCubeMapTexture(const std::string& posX, const std::string& negX, const std::string& posY,
	const std::string& negY, const std::string& posZ, const std::string& negZ, bool flipImageOnLoad) {
	constexpr int cubeSize = 6;

	std::string cubeMapFile[cubeSize]{
		posX, negX,
		posY, negY,
		posZ, negZ
	};

	CubeMapInfo texInfo{ };
	glGenTextures(1, &texInfo.id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texInfo.id);

	for (int i = 0; i < cubeSize; ++i) {
		stbi_set_flip_vertically_on_load(flipImageOnLoad);

		unsigned char* imageData = stbi_load(cubeMapFile[i].c_str(), &texInfo.width[i], &texInfo.height[i], &texInfo.nrChannel[i], 0);
		if (!imageData) {
			std::cerr << "texture file path wrong: not exist texture file, file name{ " << cubeMapFile[i] << " }";
			exit(EXIT_FAILURE);
		}
		std::cout << "texture file load success : file name{ " << cubeMapFile[i] << " }\n";

		int channel{ };
		switch (texInfo.nrChannel[i]) {
		case 1:
			channel = GL_RED;
			break;
		case 3:
			channel = GL_RGB;
			break;
		case 4:
			channel = GL_RGBA;
			break;
		}

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, channel, texInfo.width[i], texInfo.height[i], 0, channel, GL_UNSIGNED_BYTE, (void*)imageData);

		stbi_image_free(imageData);
	}
	SetCubeMapTextureOption();

	m_cubeMaps.push_back(texInfo);
}

void CubeMapTexture::BindCubeMap(int cubeMapIndex) {
	glActiveTexture(GL_TEXTURE0 + cubeMapIndex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeMaps[cubeMapIndex].id);
}

void CubeMapTexture::UnBindCubeMap() {
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
