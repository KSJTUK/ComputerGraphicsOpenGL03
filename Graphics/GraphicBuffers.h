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
	unsigned int m_modelParentTransformLocation{ };
	unsigned int m_modelInitTransformLocation{ };
	unsigned int m_objectColorLocation{ };

public:
	void Init();

	void SetVerticies(const std::vector<Vertex>& verticies);
	void BindingTexture(const uint32& textureID);

	void SetDrawMode(unsigned int mode);
	void Render();
};