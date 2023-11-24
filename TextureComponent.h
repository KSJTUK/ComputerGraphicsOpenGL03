#pragma once

class TextureComponent {
public:
	TextureComponent();
	~TextureComponent();

private:
	std::vector<TextureInfo> m_textures{ };

public:
	static void SetTextureDefaultOption();

	void LoadTexture(const std::string& textureFilePath, int channel, bool flipImageOnLoad);

	void BindingTexture(int textureIndex);
	void UnBindingTextures();

	uint32 GetTextureID(int textureIndex);
	const TextureInfo& GetTextureInfo(int textureIndex) const;
};