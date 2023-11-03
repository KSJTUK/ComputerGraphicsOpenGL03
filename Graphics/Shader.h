#pragma once

class Shader {
private:
	Shader();
	~Shader();

private:
	static Shader* m_instance;

public:
	static Shader* GetInstance();
	static void Destroy();

private:
	unsigned int m_shaderProgram{ };
	unsigned int m_fragmentShader{ };
	unsigned int m_vertexShader{ };

	// ���̴� ������ ������ ������ ����
	char* m_vertexShaderFileContents{ };
	char* m_fragmentShaderFileContents{ };

public:
	// ���̴� ���� ������ �ҷ����� �Լ�
	void RoadVertexShaderFile(const char* filePath);
	void RoadFragmentShaderFile(const char* filePaht);

	// ���̴� �ۼ� �Լ���
	void CompileShaders();
	void AttachAndLinkShaders();
	void CreateShaderProgram();

	// program ���
	void UseProgram();
	void UnUseProgram();

	// �亯ȯ ��� ���� �Լ�
	void SetViewMat(const glm::mat4& viewMat);

	// ������ȯ ��� ���� �Լ�
	void SetPerspectiveMat(const glm::mat4& perspectiveMat);

	// ������ ������ ���� �Լ�
	void SetUniformMat4(const std::string& valName, const glm::mat4& matrix);
	void SetUniformMat3(const std::string& valName, const glm::mat3& matrix);
	void SetUniformMat2(const std::string& valName, const glm::mat2& matrix);
	void SetUniformVec4(const std::string& valName, const glm::vec4& vector);
	void SetUniformVec3(const std::string& valName, const glm::vec3& vector);
	void SetUniformVec2(const std::string& valName, const glm::vec2& vector);
	void SetUniformFloat(const std::string& valueName, const float& fValue);

public:
	// Getter �Լ���
	unsigned int GetShaderProgramID() const { return m_shaderProgram; }
};

