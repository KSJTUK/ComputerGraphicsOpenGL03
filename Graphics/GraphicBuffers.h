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

	// Element Buffer OBject ID
	unsigned int m_elementBuffer{ };

	size_t m_vertexDataSize{ };
	size_t m_indexDataSize{ };

	// �׸��� ��� ��, ��, �ﰢ�� ��
	// default���� �ﰢ��(�����ڿ��� ����)
	unsigned int m_drawMode{ };

	// �� ��ȯ ��� ������ ��ġ ����
	unsigned int m_modelTransformLocation{ };
	unsigned int m_modelParentTransformLocation{ };
	unsigned int m_modelInitTransformLocation{ };

public:
	void Init(unsigned int shaderProgramID);

	void SetInitTransformMat(const glm::mat4& initTrans);
	void SetTransformMat(glm::mat4& trans);
	void SetParentTransformMat(const glm::mat4& parentTrans);

	void SetVerticies(const Vertex* verticies, unsigned int dataSize);
	void SetVerticies(const std::vector<Vertex>& verticies);

	void SetIndexBuffer(unsigned int* indexBuffer, size_t bufferSize);
	void SetIndexBuffer(const std::vector<unsigned int>& indicies);

	void SetDrawMode(unsigned int mode);
	void Render();
};