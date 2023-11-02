#include "pch.h"
#include "Model/Model.h"
#include "Graphics/GraphicBuffers.h"
#include "Graphics/Shader.h"

Model::Model(const std::string& objectFilePath) {
	ReadObject(objectFilePath.c_str());
}

Model::~Model() { }

void Model::CalcMinMaxVertexElem() {
	auto minAndMaxX = std::minmax_element(m_verticies.begin(), m_verticies.end(),
		[](const Vertex& v1, const Vertex& v2) {
			return v1.position.x < v2.position.x;
		}
	);

	auto minAndMaxY = std::minmax_element(m_verticies.begin(), m_verticies.end(),
		[](const Vertex& v1, const Vertex& v2) {
			return v1.position.y < v2.position.y;
		}
	);

	auto minAndMaxZ = std::minmax_element(m_verticies.begin(), m_verticies.end(),
		[](const Vertex& v1, const Vertex& v2) {
			return v1.position.z < v2.position.z;
		}
	);

	m_maxCoord = glm::vec3{ minAndMaxX.second->position.x, minAndMaxY.second->position.y, minAndMaxZ.second->position.z };
	m_minCoord = glm::vec3{ minAndMaxX.first->position.x, minAndMaxY.first->position.y, minAndMaxZ.first->position.z };
}

void Model::MakeBoundingBox() {
	m_boundingBox = { m_maxCoord, m_minCoord };
}

void Model::ReadFace(std::stringstream& contents, std::vector<unsigned int>* indiciesVec) {
	std::string delTag{ };
	std::string face[3]{ };        // f a/b/c -> a == 정점 인덱스, b == 텍스처 인덱스, c == 노멀 인덱스
	contents >> delTag >> face[0] >> face[1] >> face[2];

	for (int i = 0; i < 3; ++i) {
		std::string temp{ };
		int cnt{ };
		int faceSize{ static_cast<int>(face[i].size()) };
		for (int c = 0; faceSize; ++c) {
			if (face[i][c] == '\0') {
				indiciesVec[cnt].push_back(std::stoi(temp) - 1);
				break;
			}

			if (face[i][c] == '/') {
				if (!temp.empty()) {
					indiciesVec[cnt].push_back(std::stoi(temp) - 1);
				}
				cnt++;
				temp.clear();
			}
			else {
				temp += face[i][c];
			}
		}
	}
}

void Model::ReadVertex(std::stringstream& contents, uint32& vertexCount) {
	std::string delTag{ };
	glm::vec3 tempVec{ };      // 정점 좌표 저장
	contents >> delTag >> tempVec.x >> tempVec.y >> tempVec.z;
	if (m_verticies.size() == vertexCount) {
		m_verticies.push_back(Vertex{ tempVec, glm::linearRand(glm::vec3{ }, glm::vec3{ 1.f }), glm::vec2{} });
	}
	else {
		m_verticies[vertexCount].position = tempVec;
	}
	++vertexCount;
}

void Model::ReadVertexTexture(std::stringstream& contents, uint32& textureCount) {
	std::string delTag{ };
	glm::vec2 tempVec{ };
	contents >> delTag >> tempVec.x >> tempVec.y;
	if (m_verticies.size() == textureCount) {
		m_verticies.push_back(Vertex{ glm::vec3{ }, glm::linearRand(glm::vec3{ }, glm::vec3{ 1.f }), tempVec, glm::vec3{ } });
	}
	else {
		m_verticies[textureCount].texture = tempVec;
	}
	++textureCount;
}

void Model::ReadVertexNormal(std::stringstream& contents, uint32& normalCount) {
	std::string delTag{ };
	glm::vec3 tempVec{ };      // 정점 노멀 저장
	contents >> delTag >> tempVec.x >> tempVec.y >> tempVec.z;
	if (m_verticies.size() == normalCount) {
		m_verticies.push_back(Vertex{ glm::vec3{ }, glm::linearRand(glm::vec3{ }, glm::vec3{ 1.f }), glm::vec2{ }, tempVec });
	}
	else {
		m_verticies[normalCount].normal = tempVec;
	}
	++normalCount;
}

void Model::ReadObject(const char* filePath) {
	std::ifstream objFile{ filePath, std::ios::in };

	std::vector<unsigned int> indiciesVec[3]{ }; // cnt: 0 == vertex, 1 == texture, 2 == nomal

	uint32 vertexCount{ };
	uint32 textureCount{ };
	uint32 normalCount{ };

	if (!objFile.is_open()) {
		assert(0);
	}

	std::string line{ "" };
	while (!objFile.eof()) {
		std::getline(objFile, line);
		std::stringstream sstream{ line };
		std::string delTag{ };     // 앞에 있는 v, vn, f와 같은 태그 제거용

		if (line[0] == 'v') {              // 맨 앞 문자가 v이면 정점에 대한 정보이다
			if (line[1] == 'n') {          // vn == 정점 노멀
				ReadVertexNormal(sstream, normalCount);
			}
			else if (line[1] == 't') {		// vt == 텍스쳐 좌표
				ReadVertexTexture(sstream, textureCount);
			}
			else if (line[1] == ' ') {     // v == 정점 좌표
				ReadVertex(sstream, vertexCount);
			}
		}
		else if (line[0] == 'f') {         // 맨 앞 문자가 f이면 face(면)에 대한 정보이다
			ReadFace(sstream, indiciesVec);
		}
	}

	if (m_verticies.empty()) {
		assert(0);
	}

	if (m_verticies.size() > vertexCount) {
		m_verticies.erase(m_verticies.begin() + vertexCount - 1, m_verticies.end());
	}

	m_vertexIndicies = indiciesVec[0];
	m_vertexNormalIndicies = indiciesVec[1];
	m_textureIndicies = indiciesVec[2];

	CalcMinMaxVertexElem();
	MakeBoundingBox();
}

glm::mat4 Model::GetModelTransformMat() const {
	return m_modelTransform;
}

void Model::SetDrawMode(int drawMode) {
	m_graphicsBuffer->SetDrawMode(drawMode);
}

void Model::SetInitTransformMat(const glm::mat4& initTarnsformMat) {
	m_modelInitTransform = initTarnsformMat;
}

void Model::SetTransformMat(const glm::mat4& transformMat) {
	m_modelTransform = transformMat;
}

void Model::SetParentModelTransformMat(const glm::mat4& parentTransformMat) {
	m_modelParentTransform = parentTransformMat;
}

void Model::Init() {
	m_graphicsBuffer = std::make_unique<class GraphicBuffers>();
	m_graphicsBuffer->Init(SHADER->GetShaderProgramID());

	m_graphicsBuffer->SetVerticies(m_verticies);
	m_graphicsBuffer->SetIndexBuffer(m_vertexIndicies);
}

void Model::Update() {
}

void Model::Render() {
	m_graphicsBuffer->SetInitTransformMat(m_modelInitTransform);
	m_graphicsBuffer->SetTransformMat(m_modelTransform);
	m_graphicsBuffer->SetParentTransformMat(m_modelParentTransform);
	m_graphicsBuffer->Render();
}
