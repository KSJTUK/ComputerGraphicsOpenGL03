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

	// 쉐이더 소스코드 불러오기
	glShaderSource(m_vertexShader, 1, &m_vertexShaderFileContents, NULL);
	glShaderSource(m_fragmentShader, 1, &m_fragmentShaderFileContents, NULL);

	// 쉐이더 컴파일
	glCompileShader(m_vertexShader);
	glCompileShader(m_fragmentShader);

	// 쉐이더 컴파일 여부 확인
	int result{ };
	char errLog[BUFSIZ]{ };

	glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(m_vertexShader, sizeof(errLog), NULL, errLog);
		std::cout << errLog << std::endl;
	}

	glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(m_fragmentShader, sizeof(errLog), NULL, errLog);
		std::cout << std::string{ errLog } << std::endl;
	}
}

void Shader::AttachAndLinkShaders() {
	glAttachShader(m_shaderProgram, m_vertexShader);
	glAttachShader(m_shaderProgram, m_fragmentShader);

	// 쉐이더 링크
	glLinkProgram(m_shaderProgram);

	// 쉐이더들이 제대로 링크 되었는지 확인
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
	int viewMatLocation = glGetUniformLocation(m_shaderProgram, "viewMat");
	if (viewMatLocation == -1) {
		assert(0);
	}
	glUniformMatrix4fv(viewMatLocation, 1, GL_FALSE, glm::value_ptr(viewMat));
}

void Shader::SetPerspectiveMat(const glm::mat4& perspectiveMat) {
	int perspectiveMatLocation = glGetUniformLocation(m_shaderProgram, "perspectiveMat");
	if (perspectiveMatLocation == -1) {
		assert(0);
	}
	glUniformMatrix4fv(perspectiveMatLocation, 1, GL_FALSE, glm::value_ptr(perspectiveMat));
}

void Shader::SetUniformMat4(const std::string& valName, const glm::mat4& matrix) {
	int valLocation{ glGetUniformLocation(m_shaderProgram, valName.c_str()) };
	assert(!(valLocation == -1));
	glUniformMatrix4fv(valLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetUniformMat3(const std::string& valName, const glm::mat3& matrix) {
	int valLocation{ glGetUniformLocation(m_shaderProgram, valName.c_str()) };
	assert(!(valLocation == -1));
	glUniformMatrix3fv(valLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetUniformMat2(const std::string& valName, const glm::mat2& matrix) {
	int valLocation{ glGetUniformLocation(m_shaderProgram, valName.c_str()) };
	assert(!(valLocation == -1));
	glUniformMatrix2fv(valLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetUniformVec4(const std::string& valName, const glm::vec4& vector) {
	int valLocation{ glGetUniformLocation(m_shaderProgram, valName.c_str()) };
	assert(!(valLocation == -1));
	glUniform4fv(valLocation, 1, glm::value_ptr(vector));
}

void Shader::SetUniformVec3(const std::string& valName, const glm::vec3& vector) {
	int valLocation{ glGetUniformLocation(m_shaderProgram, valName.c_str()) };
	assert(!(valLocation == -1));
	glUniform3fv(valLocation, 1, glm::value_ptr(vector));
}

void Shader::SetUniformVec2(const std::string& valName, const glm::vec2& vector) {
	int valLocation{ glGetUniformLocation(m_shaderProgram, valName.c_str()) };
	assert(!(valLocation == -1));
	glUniform2fv(valLocation, 1, glm::value_ptr(vector));
}

void Shader::SetUniformFloat(const std::string& valName, const float& fValue) {
	int valLocation{ glGetUniformLocation(m_shaderProgram, valName.c_str()) };
	assert(!(valLocation == -1));
	glUniform1f(valLocation, fValue);
}

// Light Object Shader
// -------------------------------------------------------------------------------
LightObjectShader* LightObjectShader::m_instance = nullptr;

LightObjectShader::LightObjectShader() { }

LightObjectShader::~LightObjectShader() {
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

LightObjectShader* LightObjectShader::GetInstance() {
	if (!m_instance) {
		m_instance = new LightObjectShader{ };
	}
	return m_instance;
}

void LightObjectShader::Destroy() {
	if (m_instance) {
		delete m_instance;
	}
}

void LightObjectShader::RoadVertexShaderFile(const char* filePath) {
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

void LightObjectShader::RoadFragmentShaderFile(const char* filePath) {
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

void LightObjectShader::CompileShaders() {
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// 쉐이더 소스코드 불러오기
	glShaderSource(m_vertexShader, 1, &m_vertexShaderFileContents, NULL);
	glShaderSource(m_fragmentShader, 1, &m_fragmentShaderFileContents, NULL);

	// 쉐이더 컴파일
	glCompileShader(m_vertexShader);
	glCompileShader(m_fragmentShader);

	// 쉐이더 컴파일 여부 확인
	int result{ };
	char errLog[BUFSIZ]{ };

	glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(m_vertexShader, sizeof(errLog), NULL, errLog);
		std::cout << errLog << std::endl;
	}

	glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(m_fragmentShader, sizeof(errLog), NULL, errLog);
		std::cout << std::string{ errLog } << std::endl;
	}
}

void LightObjectShader::AttachAndLinkShaders() {
	glAttachShader(m_shaderProgram, m_vertexShader);
	glAttachShader(m_shaderProgram, m_fragmentShader);

	// 쉐이더 링크
	glLinkProgram(m_shaderProgram);

	// 쉐이더들이 제대로 링크 되었는지 확인
	int result{ };
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &result);
	if (!result) {
		throw "Shaders are not Linked";
	}
}

void LightObjectShader::CreateShaderProgram() {
	m_shaderProgram = glCreateProgram();
	RoadVertexShaderFile(".\\Shader\\light_object_vshader.glsl");
	RoadFragmentShaderFile(".\\Shader\\light_object_fshader.glsl");
	CompileShaders();
	AttachAndLinkShaders();
}

void LightObjectShader::UseProgram() {
	glUseProgram(m_shaderProgram);
}

void LightObjectShader::UnUseProgram() {
	glUseProgram(0);
}

void LightObjectShader::SetViewMat(const glm::mat4& viewMat) {
	int viewMatLocation = glGetUniformLocation(m_shaderProgram, "view");
	assert(!(viewMatLocation == -1));
	glUniformMatrix4fv(viewMatLocation, 1, GL_FALSE, glm::value_ptr(viewMat));
}

void LightObjectShader::SetPerspectiveMat(const glm::mat4& perspectiveMat) {
	int perspectiveMatLocation = glGetUniformLocation(m_shaderProgram, "perspective");
	assert(!(perspectiveMatLocation == -1));
	glUniformMatrix4fv(perspectiveMatLocation, 1, GL_FALSE, glm::value_ptr(perspectiveMat));
}

void LightObjectShader::SetUniformMat4(const std::string& valName, const glm::mat4& matrix) {
	int valLocation{ glGetUniformLocation(m_shaderProgram, valName.c_str()) };
	assert(!(valLocation == -1));
	glUniformMatrix4fv(valLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void LightObjectShader::SetUniformMat3(const std::string& valName, const glm::mat3& matrix) {
	int valLocation{ glGetUniformLocation(m_shaderProgram, valName.c_str()) };
	assert(!(valLocation == -1));
	glUniformMatrix3fv(valLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void LightObjectShader::SetUniformMat2(const std::string& valName, const glm::mat2& matrix) {
	int valLocation{ glGetUniformLocation(m_shaderProgram, valName.c_str()) };
	assert(!(valLocation == -1));
	glUniformMatrix2fv(valLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void LightObjectShader::SetUniformVec4(const std::string& valName, const glm::vec4& vector) {
	int valLocation{ glGetUniformLocation(m_shaderProgram, valName.c_str()) };
	assert(!(valLocation == -1));
	glUniform4fv(valLocation, 1, glm::value_ptr(vector));
}

void LightObjectShader::SetUniformVec3(const std::string& valName, const glm::vec3& vector) {
	int valLocation{ glGetUniformLocation(m_shaderProgram, valName.c_str()) };
	assert(!(valLocation == -1));
	glUniform3fv(valLocation, 1, glm::value_ptr(vector));
}

void LightObjectShader::SetUniformVec2(const std::string& valName, const glm::vec2& vector) {
	int valLocation{ glGetUniformLocation(m_shaderProgram, valName.c_str()) };
	assert(!(valLocation == -1));
	glUniform2fv(valLocation, 1, glm::value_ptr(vector));
}

void LightObjectShader::SetUniformFloat(const std::string& valName, const float& fValue) {
	int valLocation{ glGetUniformLocation(m_shaderProgram, valName.c_str()) };
	assert(!(valLocation == -1));
	glUniform1f(valLocation, fValue);
}
