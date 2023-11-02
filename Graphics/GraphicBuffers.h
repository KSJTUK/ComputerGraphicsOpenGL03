#pragma once

// VAO, VBO, EBO를 바인딩해서 삼각형을 그려줄 클래스
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

	// 그리기 모드 점, 선, 삼각형 등
	// default값은 삼각형(생성자에서 설정)
	unsigned int m_drawMode{ };

	// 모델 변환 행렬 변수의 위치 저장
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