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

	// 쉐이더 파일의 내용을 저장할 변수
	std::string m_vertexShaderFileContents{ };
	std::string m_fragmentShaderFileContents{ };
	std::string m_tesselationControlFileContents{ };
	std::string m_tesselationEvaluationFileContents{ };

public:
	// 쉐이더 파일 내용을 불러오는 함수
	void LoadVertexShaderFile(const char* filePath);
	void LoadFragmentShaderFile(const char* filePaht);
	void LoadTesselationControlShaderFile(const char* filePath);
	void LoadTesselationEvaluationShaderFile(const char* filePath);

	// 쉐이더 작성 함수들
	void CompileShaders();
	void AttachAndLinkShaders();
	void CreateShaderProgram();

	// program 사용
	void UseProgram();
	void UnUseProgram();

	// 뷰변환 행렬 세팅 함수
	void SetViewMat(const glm::mat4& viewMat);

	// 투영변환 행렬 세팅 함수
	void SetPerspectiveMat(const glm::mat4& perspectiveMat);

	// 유니폼 변수들 세팅 함수
	void SetUniformMat4(const std::string& valName, const glm::mat4& matrix);
	void SetUniformMat3(const std::string& valName, const glm::mat3& matrix);
	void SetUniformMat2(const std::string& valName, const glm::mat2& matrix);
	void SetUniformVec4(const std::string& valName, const glm::vec4& vector);
	void SetUniformVec3(const std::string& valName, const glm::vec3& vector);
	void SetUniformVec2(const std::string& valName, const glm::vec2& vector);
	void SetUniformFloat(const std::string& valueName, const float& fValue);
	void SetUniformInt(const std::string& valName, const int& iValue);

public:
	// Getter 함수들
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

	// 쉐이더 파일의 내용을 저장할 변수
	char* m_vertexShaderFileContents{ };
	char* m_fragmentShaderFileContents{ };

public:
	// 쉐이더 파일 내용을 불러오는 함수
	void RoadVertexShaderFile(const char* filePath);
	void RoadFragmentShaderFile(const char* filePaht);

	// 쉐이더 작성 함수들
	void CompileShaders();
	void AttachAndLinkShaders();
	void CreateShaderProgram();

	// program 사용
	void UseProgram();
	void UnUseProgram();

	// 뷰변환 행렬 세팅 함수
	void SetViewMat(const glm::mat4& viewMat);

	// 투영변환 행렬 세팅 함수
	void SetPerspectiveMat(const glm::mat4& perspectiveMat);

	// 유니폼 변수들 세팅 함수
	void SetUniformMat4(const std::string& valName, const glm::mat4& matrix);
	void SetUniformMat3(const std::string& valName, const glm::mat3& matrix);
	void SetUniformMat2(const std::string& valName, const glm::mat2& matrix);
	void SetUniformVec4(const std::string& valName, const glm::vec4& vector);
	void SetUniformVec3(const std::string& valName, const glm::vec3& vector);
	void SetUniformVec2(const std::string& valName, const glm::vec2& vector);
	void SetUniformFloat(const std::string& valueName, const float& fValue);

public:
	// Getter 함수들
	unsigned int GetShaderProgramID() const { return m_shaderProgram; }
};

