#include "pch.h"
#include "Graphics/Shader.h"

Shader* Shader::m_instance = nullptr;

Shader::Shader() { }

Shader::~Shader() {
	if (m_vertexShaderFileContents) {
		delete[] m_vertexShaderFileContents;
	}

	if (m_fragmentShaderFileContents) {
		delete[] m_fragmentShaderFileContents;
	}

	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);
	glDeleteProgram(m_shaderProgram);
}

Shader* Shader::GetInstance() {
	if (!m_instance) {
		m_instance = new Shader{ };
	}
	return m_instance;
}

void Shader::Destroy() {
	if (m_instance) {
		delete m_instance;
	}
}

void Shader::RoadVertexShaderFile(const char* filePath) {
	std::fstream vertexFile{ filePath, std::ios::in };

	if (!vertexFile.is_open()) {
		throw "vertex shader file open error";
	}


	std::string contents{ };
	std::string line{ " " };
	while (!vertexFile.eof()) {
		std::getline(vertexFile, line);
		contents.append(line + "\n");
	}

	std::string::size_type size = contents.size();
	m_vertexShaderFileContents = new char[size + 1] {};
	memcpy(m_vertexShaderFileContents, contents.c_str(), size + 1);

	vertexFile.close();
}

void Shader::RoadFragmentShaderFile(const char* filePath) {
	std::fstream fragmentFile{ filePath, std::ios::in };

	if (!fragmentFile.is_open()) {
		throw "fragment shader file open error";
	}

	std::string contents{ };
	std::string line{ " " };
	while (!fragmentFile.eof()) {
		std::getline(fragmentFile, line);
		contents.append(line + "\n");
	}

	std::string::size_type size = contents.size();
	m_fragmentShaderFileContents = new char[size + 1] {};
	memcpy(m_fragmentShaderFileContents, contents.c_str(), size + 1);

	fragmentFile.close();
}

void Shader::CompileShaders() {
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// ���̴� �ҽ��ڵ� �ҷ�����
	glShaderSource(m_vertexShader, 1, &m_vertexShaderFileContents, NULL);
	glShaderSource(m_fragmentShader, 1, &m_fragmentShaderFileContents, NULL);

	// ���̴� ������
	glCompileShader(m_vertexShader);
	glCompileShader(m_fragmentShader);

	// ���̴� ������ ���� Ȯ��
	int result{ };
	char errLog[BUFSIZ]{ };

	glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(m_vertexShader, sizeof(errLog), NULL, errLog);
		throw std::string{ "vertex shader ������ ����: " + std::string{ errLog } };
	}

	glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(m_fragmentShader, sizeof(errLog), NULL, errLog);
		throw std::string{ "fragment shader ������ ����: " + std::string{ errLog } };
	}
}

void Shader::AttachAndLinkShaders() {
	glAttachShader(m_shaderProgram, m_vertexShader);
	glAttachShader(m_shaderProgram, m_fragmentShader);

	// ���̴� ��ũ
	glLinkProgram(m_shaderProgram);

	// ���̴����� ����� ��ũ �Ǿ����� Ȯ��
	int result{ };
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &result);
	if (!result) {
		throw "Shaders are not Linked";
	}
}

void Shader::CreateShaderProgram() {
	m_shaderProgram = glCreateProgram();
	RoadVertexShaderFile(".\\Shader\\vertex_shader.glsl");
	RoadFragmentShaderFile(".\\Shader\\fragment_shader.glsl");
	CompileShaders();
	AttachAndLinkShaders();
}

void Shader::UseProgram() {
	glUseProgram(m_shaderProgram);
}

void Shader::UnUseProgram() {
	glUseProgram(0);
}

void Shader::SetViewMat(const glm::mat4& viewMat) {
	unsigned int viewMatLocation = glGetUniformLocation(m_shaderProgram, "viewMat");
	if (viewMatLocation == -1) {
		assert(0);
	}
	glUniformMatrix4fv(viewMatLocation, 1, GL_FALSE, glm::value_ptr(viewMat));
}

void Shader::SetPerspectiveMat(const glm::mat4& perspectiveMat) {
	unsigned int perspectiveMatLocation = glGetUniformLocation(m_shaderProgram, "perspectiveMat");
	if (perspectiveMatLocation == -1) {
		assert(0);
	}
	glUniformMatrix4fv(perspectiveMatLocation, 1, GL_FALSE, glm::value_ptr(perspectiveMat));
}
