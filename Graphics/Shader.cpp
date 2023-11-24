#include "pch.h"
#include "Graphics/Shader.h"

Shader::Shader() { }

Shader::~Shader() { }

void Shader::LoadVertexShaderFile(const char* filePath) {
	std::fstream vertexFile{ filePath, std::ios::in };

	if (!vertexFile.is_open()) {
		throw "vertex shader file open error";
	}


	m_vertexShaderFileContents = { "" };
	std::string line{ " " };
	while (!vertexFile.eof()) {
		std::getline(vertexFile, line);
		m_vertexShaderFileContents.append(line + "\n");
	}

	vertexFile.close();
}

void Shader::LoadFragmentShaderFile(const char* filePath) {
	std::fstream fragmentFile{ filePath, std::ios::in };

	if (!fragmentFile.is_open()) {
		throw "fragment shader file open error";
	}

	m_fragmentShaderFileContents = { "" };
	std::string line{ " " };
	while (!fragmentFile.eof()) {
		std::getline(fragmentFile, line);
		m_fragmentShaderFileContents.append(line + "\n");
	}


	fragmentFile.close();
}

void Shader::LoadTesselationControlShaderFile(const char* filePath) {
	std::fstream tesselationControlFile{ filePath, std::ios::in };

	if (!tesselationControlFile.is_open()) {
		throw "tesselation control shader file open error";
	}

	m_tesselationControlFileContents = { "" };
	std::string line{ " " };
	while (!tesselationControlFile.eof()) {
		std::getline(tesselationControlFile, line);
		m_tesselationControlFileContents.append(line + "\n");
	}


	tesselationControlFile.close();
}

void Shader::LoadTesselationEvaluationShaderFile(const char* filePath) {
	std::fstream tesselationEvaluationFile{ filePath, std::ios::in };

	if (!tesselationEvaluationFile.is_open()) {
		throw "tesselation evaluate shader file open error";
	}

	m_tesselationEvaluationFileContents = { "" };
	std::string line{ " " };
	while (!tesselationEvaluationFile.eof()) {
		std::getline(tesselationEvaluationFile, line);
		m_tesselationEvaluationFileContents.append(line + "\n");
	}


	tesselationEvaluationFile.close();
}

void Shader::LoadGeometryShader(const char* filePath) {
	std::fstream geometryFile{ filePath, std::ios::in };

	if (!geometryFile.is_open()) {
		throw "tesselation evaluate shader file open error";
	}

	m_geometryShaderFileContents = { "" };
	std::string line{ " " };
	while (!geometryFile.eof()) {
		std::getline(geometryFile, line);
		m_geometryShaderFileContents.append(line + "\n");
	}

	geometryFile.close();
}

void Shader::UseProgram() {
	glUseProgram(m_shaderProgram);
}

void Shader::UnUseProgram() {
	glUseProgram(0);
}

void Shader::CheckAndPrintShaderCompileError(const uint32& shaderID) {
	int result{ };
	char errLog[BUFSIZ]{ };
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(shaderID, sizeof(errLog), NULL, errLog);
		std::cout << std::string{ errLog } << std::endl;
	}
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
	glUniform1fv(valLocation, 1, &fValue);
}

void Shader::SetUniformInt(const std::string& valName, const int& iValue) {
	int valLocation{ glGetUniformLocation(m_shaderProgram, valName.c_str()) };
	assert(!(valLocation == -1));
	glUniform1iv(valLocation, 1, &iValue);
}

void Shader::SetUniformBool(const std::string& valName, const int& bValue) {
	int valLocation{ glGetUniformLocation(m_shaderProgram, valName.c_str()) };
	assert(!(valLocation == -1));
	glUniform1iv(valLocation, 1, &bValue);
}

ObjectShader* ObjectShader::m_instance = nullptr;

ObjectShader::ObjectShader() { }

ObjectShader::~ObjectShader() {
	glDeleteShader(m_tesselEvaluationShader);
	glDeleteShader(m_tesselControlShader);
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);
	glDeleteProgram(m_shaderProgram);
}

ObjectShader* ObjectShader::GetInstance() {
	if (!m_instance) {
		m_instance = new ObjectShader{ };
	}
	return m_instance;
}

void ObjectShader::Destroy() {
	if (m_instance) {
		delete m_instance;
	}
}

void ObjectShader::CompileShaders() {
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	m_tesselControlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
	m_tesselEvaluationShader = glCreateShader(GL_TESS_EVALUATION_SHADER);

	// ���̴� �ҽ��ڵ� �ҷ�����
	const char* contentsPath = m_vertexShaderFileContents.c_str();
	glShaderSource(m_vertexShader, 1, &contentsPath, NULL);

	contentsPath = m_fragmentShaderFileContents.c_str();
	glShaderSource(m_fragmentShader, 1, &contentsPath, NULL);

	contentsPath = m_tesselationControlFileContents.c_str();
	glShaderSource(m_tesselControlShader, 1, &contentsPath, NULL);

	contentsPath = m_tesselationEvaluationFileContents.c_str();
	glShaderSource(m_tesselEvaluationShader, 1, &contentsPath, NULL);

	// ���̴� ������
	glCompileShader(m_vertexShader);
	glCompileShader(m_tesselControlShader);
	glCompileShader(m_tesselEvaluationShader);
	glCompileShader(m_fragmentShader);

	// ���̴� ������ ���� Ȯ��
	CheckAndPrintShaderCompileError(m_vertexShader);
	CheckAndPrintShaderCompileError(m_tesselControlShader);
	CheckAndPrintShaderCompileError(m_tesselEvaluationShader);
	CheckAndPrintShaderCompileError(m_fragmentShader);
}

void ObjectShader::AttachAndLinkShaders() {
	glAttachShader(m_shaderProgram, m_vertexShader);
	glAttachShader(m_shaderProgram, m_tesselControlShader);
	glAttachShader(m_shaderProgram, m_tesselEvaluationShader);
	glAttachShader(m_shaderProgram, m_fragmentShader);

	// ���̴� ��ũ
	glLinkProgram(m_shaderProgram);

	// ���̴����� ����� ��ũ �Ǿ����� Ȯ��
	int result{ };
	char errLog[BUFSIZ]{ };
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(m_shaderProgram, sizeof(errLog), NULL, errLog);
		std::cerr << std::string{ errLog } << std::endl;
		throw "Shaders are not Linked";
	}
}

void ObjectShader::CreateShaderProgram() {
	m_shaderProgram = glCreateProgram();
	LoadVertexShaderFile(".\\Shader\\object_vertex_shader.glsl");
	LoadFragmentShaderFile(".\\Shader\\object_fragment_shader.glsl");
	LoadTesselationControlShaderFile(".\\Shader\\object_tessel_control_shader.glsl");
	LoadTesselationEvaluationShaderFile(".\\Shader\\object_tessel_evaluation_shader.glsl");
	//LoadGeometryShader(".\\Shader\\geometry_shader.glsl");
	CompileShaders();
	AttachAndLinkShaders();
}

// Light Object Shader
// -------------------------------------------------------------------------------
LightObjectShader* LightObjectShader::m_instance = nullptr;

LightObjectShader::LightObjectShader() { }

LightObjectShader::~LightObjectShader() {
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

void LightObjectShader::CompileShaders() {
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// ���̴� �ҽ��ڵ� �ҷ�����
	const char* contentsPath = m_vertexShaderFileContents.c_str();
	glShaderSource(m_vertexShader, 1, &contentsPath, NULL);

	contentsPath = m_fragmentShaderFileContents.c_str();
	glShaderSource(m_fragmentShader, 1, &contentsPath, NULL);

	// ���̴� ������
	glCompileShader(m_vertexShader);
	glCompileShader(m_fragmentShader);

	// ���̴� ������ ���� Ȯ��
	CheckAndPrintShaderCompileError(m_vertexShader);
	CheckAndPrintShaderCompileError(m_fragmentShader);
}

void LightObjectShader::AttachAndLinkShaders() {
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

void LightObjectShader::CreateShaderProgram() {
	m_shaderProgram = glCreateProgram();
	LoadVertexShaderFile(".\\Shader\\light_object_vshader.glsl");
	LoadFragmentShaderFile(".\\Shader\\light_object_fshader.glsl");
	CompileShaders();
	AttachAndLinkShaders();
}


// ParticleShader
// ----------------------------------------------------------
ParticleShader* ParticleShader::m_instance = nullptr;

ParticleShader::ParticleShader() { }

ParticleShader::~ParticleShader() {
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);
	glDeleteProgram(m_shaderProgram);
}

ParticleShader* ParticleShader::GetInstance() {
	if (!m_instance) {
		m_instance = new ParticleShader{ };
	}
	return m_instance;
}

void ParticleShader::Destroy() {
	if (m_instance) {
		delete m_instance;
	}
}

void ParticleShader::CompileShaders() {
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	m_geometryShader = glCreateShader(GL_GEOMETRY_SHADER);

	// ���̴� �ҽ��ڵ� �ҷ�����
	const char* contentsPath = m_vertexShaderFileContents.c_str();
	glShaderSource(m_vertexShader, 1, &contentsPath, NULL);

	contentsPath = m_fragmentShaderFileContents.c_str();
	glShaderSource(m_fragmentShader, 1, &contentsPath, NULL);

	contentsPath = m_geometryShaderFileContents.c_str();
	glShaderSource(m_geometryShader, 1, &contentsPath, NULL);

	// ���̴� ������
	glCompileShader(m_vertexShader);
	glCompileShader(m_fragmentShader);
	glCompileShader(m_geometryShader);

	// ���̴� ������ ���� Ȯ��
	CheckAndPrintShaderCompileError(m_vertexShader);
	CheckAndPrintShaderCompileError(m_fragmentShader);
	CheckAndPrintShaderCompileError(m_geometryShader);
}

void ParticleShader::AttachAndLinkShaders() {
	glAttachShader(m_shaderProgram, m_vertexShader);
	glAttachShader(m_shaderProgram, m_geometryShader);
	glAttachShader(m_shaderProgram, m_fragmentShader);

	// ���̴� ��ũ
	glLinkProgram(m_shaderProgram);

	// ���̴����� ����� ��ũ �Ǿ����� Ȯ��
	int result{ };
	char errLog[BUFSIZ]{ };
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(m_shaderProgram, sizeof(errLog), NULL, errLog);
		std::cerr << std::string{ errLog } << std::endl;
		throw "Shaders are not Linked";
	}
}

void ParticleShader::CreateShaderProgram() {
	m_shaderProgram = glCreateProgram();
	LoadVertexShaderFile(".\\Shader\\particle_vertex_shader.glsl");
	LoadFragmentShaderFile(".\\Shader\\particle_fragment_shader.glsl");
	LoadGeometryShader(".\\Shader\\geometry_shader.glsl");
	CompileShaders();
	AttachAndLinkShaders();
}

// terrain shader
// ---------------------------------------------------
TerrainShader* TerrainShader::m_instance = nullptr;

TerrainShader::TerrainShader() { }

TerrainShader::~TerrainShader() {
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);
	glDeleteProgram(m_shaderProgram);
}

TerrainShader* TerrainShader::GetInstance() {
	if (!m_instance) {
		m_instance = new TerrainShader{ };
	}
	return m_instance;
}

void TerrainShader::Destroy() {
	if (m_instance) {
		delete m_instance;
	}
	m_instance = nullptr;
}

void TerrainShader::CompileShaders() {
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	m_tesselControlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
	m_tesselEvaluationShader = glCreateShader(GL_TESS_EVALUATION_SHADER);

	// ���̴� �ҽ��ڵ� �ҷ�����
	const char* contentsPath = m_vertexShaderFileContents.c_str();
	glShaderSource(m_vertexShader, 1, &contentsPath, NULL);

	contentsPath = m_fragmentShaderFileContents.c_str();
	glShaderSource(m_fragmentShader, 1, &contentsPath, NULL);

	contentsPath = m_tesselationControlFileContents.c_str();
	glShaderSource(m_tesselControlShader, 1, &contentsPath, NULL);

	contentsPath = m_tesselationEvaluationFileContents.c_str();
	glShaderSource(m_tesselEvaluationShader, 1, &contentsPath, NULL);

	// ���̴� ������
	glCompileShader(m_vertexShader);
	glCompileShader(m_tesselControlShader);
	glCompileShader(m_tesselEvaluationShader);
	glCompileShader(m_fragmentShader);

	// ���̴� ������ ���� Ȯ��
	CheckAndPrintShaderCompileError(m_vertexShader);
	CheckAndPrintShaderCompileError(m_tesselControlShader);
	CheckAndPrintShaderCompileError(m_tesselEvaluationShader);
	CheckAndPrintShaderCompileError(m_fragmentShader);
}

void TerrainShader::AttachAndLinkShaders() {
	glAttachShader(m_shaderProgram, m_vertexShader);
	glAttachShader(m_shaderProgram, m_tesselControlShader);
	glAttachShader(m_shaderProgram, m_tesselEvaluationShader);
	glAttachShader(m_shaderProgram, m_fragmentShader);

	// ���̴� ��ũ
	glLinkProgram(m_shaderProgram);

	// ���̴����� ����� ��ũ �Ǿ����� Ȯ��
	int result{ };
	char errLog[BUFSIZ]{ };
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(m_shaderProgram, sizeof(errLog), NULL, errLog);
		std::cerr << std::string{ errLog } << std::endl;
		throw "Shaders are not Linked";
	}
}

void TerrainShader::CreateShaderProgram() {
	m_shaderProgram = glCreateProgram();
	LoadVertexShaderFile(".\\Shader\\terrain_vertex_shader.glsl");
	LoadFragmentShaderFile(".\\Shader\\terrain_fragment_shader.glsl");
	LoadTesselationControlShaderFile(".\\Shader\\terrain_tessel_control_shader.glsl");
	LoadTesselationEvaluationShaderFile(".\\Shader\\terrain_tessel_evaluation_shader.glsl");
	CompileShaders();
	AttachAndLinkShaders();
}