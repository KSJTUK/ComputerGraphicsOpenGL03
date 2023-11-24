#pragma once

// VAO, VBO, EBO�� ���ε��ؼ� �ﰢ���� �׷��� Ŭ����
class GraphicBuffers {
public:
	GraphicBuffers();
	~GraphicBuffers();

private:
	// Vertex Buffer Object ID
	unsigned int m_vertexBuffer{ };

	// Vertex Array Object ID
	unsigned int m_vertexArray{ };

	size_t m_vertexDataSize{ };
	size_t m_indexDataSize{ };

	// �׸��� ��� ��, ��, �ﰢ�� ��
	// default���� �ﰢ��(�����ڿ��� ����)
	unsigned int m_drawMode{ };

public:
	void Init();

	void SetVerticies(const std::vector<Vertex>& verticies);
	void SetPatchParameters(int numOfPatches);
	void BindingTexture(const uint32& textureID);

	void SetDrawMode(unsigned int mode);
	void Render();
};