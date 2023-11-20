#include "pch.h"
#include "Graphics/GraphicBuffers.h"

GraphicBuffers::GraphicBuffers() : m_drawMode{ GL_PATCHES } { }

GraphicBuffers::~GraphicBuffers() {
	glDeleteVertexArrays(1, &m_vertexArray);
	glDeleteBuffers(1, &m_elementBuffer);
	glDeleteBuffers(1, &m_vertexBuffer);
}

void GraphicBuffers::Init() {
	// VAO ��ü ���� �� ���ε�
	// VBO ��ü ���� �� ���ε�
	glGenVertexArrays(1, &m_vertexArray);
	glGenBuffers(1, &m_vertexBuffer);

	glBindVertexArray(m_vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	// EBO ��ü ���� �� ���ε�
	glGenBuffers(1, &m_elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer); //--- GL_ELEMENT_ARRAY_BUFFER ���� �������� ���ε�
}

void GraphicBuffers::SetVerticies(const std::vector<Vertex>& verticies) {
	m_vertexDataSize = verticies.size();
	// Vertex��ü�� ������ VBO�� �Ѱ���
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

	glPatchParameteri(GL_PATCH_VERTICES, 3);
}

void GraphicBuffers::BindingTexture(const uint32& textureID) {
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void GraphicBuffers::SetDrawMode(unsigned int mode) {
	m_drawMode = mode;
}

void GraphicBuffers::Render() {
	// shaderProgram ���� UseProgram�� Ȱ��ȭ �ߴٴ� �����Ͽ� ����
	glBindVertexArray(m_vertexArray);
	glDrawArrays(m_drawMode, 0, m_vertexDataSize);
	glBindVertexArray(0); // Array ���ε� ����
}
