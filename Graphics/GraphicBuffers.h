#pragma once

// VAO, VBO, EBO�� ���ε��ؼ� �ﰢ���� �׷��� Ŭ����
class GraphicBuffers {
public:
	GraphicBuffers();
	~GraphicBuffers();

private:
	unsigned int m_shaderProgramID{ };

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
	unsigned int m_objectColorLocation{ };

public:
	void Init(unsigned int shaderProgramID);;

	void SetVerticies(const std::vector<Vertex>& verticies);

	void SetIndexBuffer(const std::vector<unsigned int>& indicies);

	void SetUniformMat4(const std::string& varName, const glm::mat4& matrix);
	void SetUniformVec3(const std::string& varName, const glm::vec3& vector);

	void SetDrawMode(unsigned int mode);
	void Render();
};