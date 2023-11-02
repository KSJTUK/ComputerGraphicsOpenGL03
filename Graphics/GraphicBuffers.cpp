#include "pch.h"
#include "Graphics/GraphicBuffers.h"

GraphicBuffers::GraphicBuffers() : m_drawMode{ GL_TRIANGLES } { }

GraphicBuffers::~GraphicBuffers() {
	glDeleteVertexArrays(1, &m_vertexArray);
	glDeleteBuffers(1, &m_elementBuffer);
	glDeleteBuffers(1, &m_vertexBuffer);
}

void GraphicBuffers::Init(unsigned int shaderProgramID) {
	// VAO 객체 생성 및 바인드
	// VBO 객체 생성 및 바인드
	glGenVertexArrays(1, &m_vertexArray);
	glGenBuffers(1, &m_vertexBuffer);

	glBindVertexArray(m_vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	// EBO 객체 생성 및 바인드
	glGenBuffers(1, &m_elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer); //--- GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩

	// 셰이더언어 파일에 있는 모델 변환 행렬 변수의 로케이션을 저장
	m_modelParentTransformLocation = glGetUniformLocation(shaderProgramID, "modelsParentTransform");
	m_modelTransformLocation = glGetUniformLocation(shaderProgramID, "modelTransform");
	m_modelInitTransformLocation = glGetUniformLocation(shaderProgramID, "modelInitTransform");

	if (m_modelInitTransformLocation == - 1 or m_modelTransformLocation == -1 or m_modelParentTransformLocation == -1) {
		assert(0);
	}
}

void GraphicBuffers::SetInitTransformMat(const glm::mat4& initTrans) {
	glUniformMatrix4fv(m_modelInitTransformLocation, 1, GL_FALSE, glm::value_ptr(initTrans));
}

void GraphicBuffers::SetTransformMat(glm::mat4& trans) {
	glUniformMatrix4fv(m_modelTransformLocation, 1, GL_FALSE, glm::value_ptr(trans));
}

void GraphicBuffers::SetParentTransformMat(const glm::mat4& parentTrans) {
	glUniformMatrix4fv(m_modelParentTransformLocation, 1, GL_FALSE, glm::value_ptr(parentTrans));
}

void GraphicBuffers::SetVerticies(const Vertex* const verticies, unsigned int dataSize) {
	m_vertexDataSize = dataSize;
	// Vertex객체의 정보를 VBO에 넘겨줌
	glBufferData(GL_ARRAY_BUFFER, dataSize * sizeof(Vertex), verticies, GL_STATIC_DRAW);

	// location 0번에 Vertex객체의 position정보를 넘겨줌
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// location 1번에 Vertex객체의 color정보를 넘겨줌
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
}

void GraphicBuffers::SetVerticies(const std::vector<Vertex>& verticies) {
	m_vertexDataSize = verticies.size();
	// Vertex객체의 정보를 VBO에 넘겨줌
	glBufferData(GL_ARRAY_BUFFER, m_vertexDataSize * sizeof(Vertex), &verticies[0], GL_STATIC_DRAW);

	// location 0번에 Vertex객체의 position정보를 넘겨줌
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// location 1번에 Vertex객체의 color정보를 넘겨줌
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
}

void GraphicBuffers::SetIndexBuffer(unsigned int* indexBuffer, size_t bufferSize) {
	// 인덱스 버퍼 내용 저장
	m_indexDataSize = bufferSize;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize * sizeof(unsigned int), indexBuffer, GL_DYNAMIC_DRAW);
}

void GraphicBuffers::SetIndexBuffer(const std::vector<unsigned int>& indicies) {
	m_indexDataSize = indicies.size();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexDataSize * sizeof(unsigned int), &indicies[0], GL_DYNAMIC_DRAW);
}

void GraphicBuffers::SetDrawMode(unsigned int mode) {
	m_drawMode = mode;
}

void GraphicBuffers::Render() {
	// shaderProgram 에서 UseProgram을 활성화 했다는 가정하에 수행
	glBindVertexArray(m_vertexArray);
	glDrawElements(m_drawMode, (GLsizei)m_indexDataSize, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0); // Array 바인드 해제
}
