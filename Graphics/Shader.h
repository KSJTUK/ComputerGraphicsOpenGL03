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
	unsigned int m_tesselControlShader{ };
	unsigned int m_tesselEvaluationShader{ };

	// ���̴� ������ ������ ������ ����
	std::string m_vertexShaderFileContents{ };
	std::string m_fragmentShaderFileContents{ };
	std::string m_tesselationControlFileContents{ };
	std::string m_tesselationEvaluationFileContents{ };

public:
	// ���̴� ���� ������ �ҷ����� �Լ�
	void LoadVertexShaderFile(const char* filePath);
	void LoadFragmentShaderFile(const char* filePaht);
	void LoadTesselationControlShaderFile(const char* filePath);
	void LoadTesselationEvaluationShaderFile(const char* filePath);

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
	void SetUniformInt(const std::string& valName, const int& iValue);

public:
	// Getter �Լ���
	unsigned int GetShaderProgramID() const { return m_shaderProgram; }
};


class LightObjectShader {
private:
	LightObjectShader();
	~LightObjectShader();

private:
	static LightObjectShader* m_instance;

public:
	static LightObjectShader* GetInstance();
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

