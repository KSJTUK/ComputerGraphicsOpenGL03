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

public:
	// Getter 함수들
	unsigned int GetShaderProgramID() const { return m_shaderProgram; }
};

