#include "pch.h"
#include "Graphics/GraphicBuffers.h"

GraphicBuffers::GraphicBuffers() : m_drawMode{ GL_TRIANGLES } { }

GraphicBuffers::~GraphicBuffers() {
	glDeleteVertexArrays(1, &m_vertexArray);
	glDeleteBuffers(1, &m_vertexBuffer);
}

void GraphicBuffers::Init() {
	// VAO ��ü ���� �� ���ε�
	// VBO ��ü ���� �� ���ε�
	glGenVertexArrays(1, &m_vertexArray);
	glGenBuffers(1, &m_vertexBuffer);

	glBindVertexArray(m_vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
}

void GraphicBuffers::ResetVerticies(const std::vector<Vertex>& verticies) {
	m_vertexDataSize = verticies.size();

	glDeleteVertexArrays(1, &m_vertexArray);

	glGenVertexArrays(1, &m_vertexArray);
	glGenBuffers(1, &m_vertexBuffer);

	glBindVertexArray(m_vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	glBufferData(GL_ARRAY_BUFFER, m_vertexDataSize * sizeof(Vertex), &verticies[0], GL_STATIC_DRAW);

	// location 0���� Vertex��ü�� position������ �Ѱ���
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// location 1���� Vertex��ü�� texture������ �Ѱ���
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));
	glEnableVertexAttribArray(1);

	// location 2���� Vertex��ü�� normal������ �Ѱ���
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);
}

void GraphicBuffers::SetVerticies(const std::vector<Vertex>& verticies) {
	m_vertexDataSize = verticies.size();

	// Vertex��ü�� ������ VBO�� �Ѱ���
	glBindVertexArray(m_vertexArray);
	glBufferData(GL_ARRAY_BUFFER, m_vertexDataSize * sizeof(Vertex), &verticies[0], GL_STATIC_DRAW);

	// location 0���� Vertex��ü�� position������ �Ѱ���
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// location 1���� Vertex��ü�� texture������ �Ѱ���
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));
	glEnableVertexAttribArray(1);

	// location 2���� Vertex��ü�� normal������ �Ѱ���
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
}

void GraphicBuffers::SetPatchParameters(int numOfPatches) {
	glPatchParameteri(GL_PATCH_VERTICES, numOfPatches);
}

void GraphicBuffers::BindingTexture(const uint32& textureID) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void GraphicBuffers::SetDrawMode(unsigned int mode) {
	m_drawMode = mode;
}

//void GraphicBuffers::Render(const uint32& textureID) {
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, textureID);
//	glBindVertexArray(m_vertexArray);
//	glDrawArrays(m_drawMode, 0, m_vertexDataSize);
//	glBindVertexArray(0); // Array ���ε� ����
//	glBindTexture(GL_TEXTURE_2D, 0);
//}

void GraphicBuffers::Render() {
	// shaderProgram ���� UseProgram�� Ȱ��ȭ �ߴٴ� �����Ͽ� ����
	glBindVertexArray(m_vertexArray);
	glDrawArrays(m_drawMode, 0, uint32(m_vertexDataSize));
	glBindVertexArray(0); // Array ���ε� ����
	glBindTexture(GL_TEXTURE_2D, 0);
}
