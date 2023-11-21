#pragma once

class TextureComponent {
public:
	TextureComponent(const std::string& textureFilePath);
	TextureComponent(const std::string& textureFilePath, bool flipImageOnLoad);
	~TextureComponent();

private:
	uint32 m_textureID{ };

	int32 m_width{ };
	int32 m_height{ };
	int32 m_nrChannels{ };

	std::string m_filePath{ };

public:
	static void SetTextureDefaultOption();

	void CreateTexture(bool flipImage=false);
	uint32 GetTextureID() const;
};
