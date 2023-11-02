#include "pch.h"
#include "Graphics/GraphicBuffers.h"

GraphicBuffers::GraphicBuffers() : m_drawMode{ GL_TRIANGLES } { }

GraphicBuffers::~GraphicBuffers() {
	glDeleteVertexArrays(1, &m_vertexArray);
	glDeleteBuffers(1, &m_elementBuffer);
	glDeleteBuffers(1, &m_vertexBuffer);
}

void GraphicBuffers::Init(unsigned int shaderProgramID) {
	m_shaderProgramID = shaderProgramID;

	// VAO 객체 생성 및 바인드
	// VBO 객체 생성 및 바인드
	glGenVertexArrays(1, &m_vertexArray);
	glGenBuffers(1, &m_vertexBuffer);

	glBindVertexArray(m_vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	// EBO 객체 생성 및 바인드
	glGenBuffers(1, &m_elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer); //--- GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩
}

void GraphicBuffers::SetVerticies(const std::vector<Vertex>& verticies) {
	m_vertexDataSize = verticies.size();
	// Vertex객체의 정보를 VBO에 넘겨줌
	glBufferData(GL_ARRAY_BUFFER, m_vertexDataSize * sizeof(Vertex), &verticies[0], GL_STATIC_DRAW);

	// location 0번에 Vertex객체의 position정보를 넘겨줌
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// location 1번에 Vertex객체의 texture정보를 넘겨줌
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));
	glEnableVertexAttribArray(1);

	// location 2번에 Vertex객체의 normal정보를 넘겨줌
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);
}

void GraphicBuffers::SetIndexBuffer(const std::vector<unsigned int>& indicies) {
	m_indexDataSize = indicies.size();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexDataSize * sizeof(unsigned int), &indicies[0], GL_DYNAMIC_DRAW);
}

void GraphicBuffers::SetUniformMat4(const std::string& varName, const glm::mat4& matrix) {
	int varLocation{ glGetUniformLocation(m_shaderProgramID, varName.c_str()) };
	assert(!(varLocation == -1));
	glUniformMatrix4fv(varLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void GraphicBuffers::SetUniformVec3(const std::string& varName, const glm::vec3& vector) {
	int varLocation{ glGetUniformLocation(m_shaderProgramID, varName.c_str()) };
	assert(!(varLocation == -1));
	glUniform3fv(varLocation, 1, glm::value_ptr(vector));
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
