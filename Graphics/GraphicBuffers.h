#pragma once

// VAO, VBO, EBO를 바인딩해서 삼각형을 그려줄 클래스
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

	// 그리기 모드 점, 선, 삼각형 등
	// default값은 삼각형(생성자에서 설정)
	unsigned int m_drawMode{ };

	// 모델 변환 행렬 변수의 위치 저장
	unsigned int m_modelTransformLocation{ };

public:
	void Init(unsigned int shaderProgramID);

	void SetTransformMat(glm::mat4& trans);

	void SetTransformMat(glm::mat4&& trans);

	void SetVerticies(const Vertex* verticies, unsigned int dataSize);
	void SetVerticies(const std::vector<Vertex>& verticies);

	void SetIndexBuffer(unsigned int* indexBuffer, size_t bufferSize);
	void SetIndexBuffer(const std::vector<unsigned int>& indicies);

	void SetDrawMode(unsigned int mode);
	void Render();
};