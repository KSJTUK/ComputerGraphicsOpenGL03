#include "pch.h"
#include "Graphics/GraphicBuffers.h"

GraphicBuffers::GraphicBuffers() : m_drawMode{ GL_TRIANGLES } { }

GraphicBuffers::~GraphicBuffers() {
	glDeleteVertexArrays(1, &m_vertexArray);
	glDeleteBuffers(1, &m_elementBuffer);
	glDeleteBuffers(1, &m_vertexBuffer);
}

void GraphicBuffers::Init(unsigned int shaderProgramID) {
	// VAO ��ü ���� �� ���ε�
	// VBO ��ü ���� �� ���ε�
	glGenVertexArrays(1, &m_vertexArray);
	glGenBuffers(1, &m_vertexBuffer);

	glBindVertexArray(m_vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	// EBO ��ü ���� �� ���ε�
	glGenBuffers(1, &m_elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer); //--- GL_ELEMENT_ARRAY_BUFFER ���� �������� ���ε�

	// ���̴���� ���Ͽ� �ִ� �� ��ȯ ��� ������ �����̼��� ����
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
	// Vertex��ü�� ������ VBO�� �Ѱ���
	glBufferData(GL_ARRAY_BUFFER, dataSize * sizeof(Vertex), verticies, GL_STATIC_DRAW);

	// location 0���� Vertex��ü�� position������ �Ѱ���
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// location 1���� Vertex��ü�� color������ �Ѱ���
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
}

void GraphicBuffers::SetVerticies(const std::vector<Vertex>& verticies) {
	m_vertexDataSize = verticies.size();
	// Vertex��ü�� ������ VBO�� �Ѱ���
	glBufferData(GL_ARRAY_BUFFER, m_vertexDataSize * sizeof(Vertex), &verticies[0], GL_STATIC_DRAW);

	// location 0���� Vertex��ü�� position������ �Ѱ���
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// location 1���� Vertex��ü�� color������ �Ѱ���
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
}

void GraphicBuffers::SetIndexBuffer(unsigned int* indexBuffer, size_t bufferSize) {
	// �ε��� ���� ���� ����
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
	// shaderProgram ���� UseProgram�� Ȱ��ȭ �ߴٴ� �����Ͽ� ����
	glBindVertexArray(m_vertexArray);
	glDrawElements(m_drawMode, (GLsizei)m_indexDataSize, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0); // Array ���ε� ����
}
