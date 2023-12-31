﻿#include "pch.h"
#include "Model/Model.h"
#include "Graphics/GraphicBuffers.h"
#include "Graphics/Shader.h"
#include "Util/TextureComponent.h"

Model::Model(const std::string& objectFilePath) {
	ReadObject(objectFilePath.c_str());
	m_textureComponent = nullptr;
}

Model::Model(const std::string& objectFilePath, const std::string& textureFilePath) {
	ReadObject(objectFilePath.c_str());
	m_textureComponent = std::make_unique<TextureComponent>();
	m_textureComponent->LoadTexture(textureFilePath, true);
}

Model::~Model() { }

void Model::CalcMinMaxVertexElem() {
	auto minAndMaxX = std::minmax_element(m_noDuplicatedVertex.begin(), m_noDuplicatedVertex.end(),
		[](const glm::vec3& v1, const glm::vec3& v2) {
			return v1.x < v2.x;
		}
	);

	auto minAndMaxY = std::minmax_element(m_noDuplicatedVertex.begin(), m_noDuplicatedVertex.end(),
		[](const glm::vec3& v1, const glm::vec3& v2) {
			return v1.y < v2.y;
		}
	);

	auto minAndMaxZ = std::minmax_element(m_noDuplicatedVertex.begin(), m_noDuplicatedVertex.end(),
		[](const glm::vec3& v1, const glm::vec3& v2) {
			return v1.z < v2.z;
		}
	);

	m_maxCoord = glm::vec3{ minAndMaxX.second->x, minAndMaxY.second->y, minAndMaxZ.second->z };
	m_minCoord = glm::vec3{ minAndMaxX.first->x, minAndMaxY.first->y, minAndMaxZ.first->z };
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

void Model::ReadVertex(std::stringstream& contents, std::vector<glm::vec3>& positions) {
	std::string delTag{ };
	glm::vec3 tempVec{ };      // 정점 좌표 저장
	contents >> delTag >> tempVec.x >> tempVec.y >> tempVec.z;
	positions.push_back(tempVec);
}

void Model::ReadVertexTexture(std::stringstream& contents, std::vector<glm::vec2>& textureCoords) {
	std::string delTag{ };
	glm::vec2 tempVec{ };      // 정점 좌표 저장
	contents >> delTag >> tempVec.x >> tempVec.y;
	textureCoords.push_back(tempVec);
}

void Model::ReadVertexNormal(std::stringstream& contents, std::vector<glm::vec3>& normals) {
	std::string delTag{ };
	glm::vec3 tempVec{ };      // 정점 좌표 저장
	contents >> delTag >> tempVec.x >> tempVec.y >> tempVec.z;
	normals.push_back(tempVec);
}

void Model::ReadObject(const char* filePath) {
	std::ifstream objFile{ filePath, std::ios::in };

	std::vector<unsigned int> indiciesVec[3]{ }; // cnt: 0 == vertex, 1 == texture, 2 == nomal

	std::vector<glm::vec3> vertexPositions{ };
	std::vector<glm::vec2> vertexTextureCoord{ };
	std::vector<glm::vec3> vertexNormals{ };

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
				ReadVertex(sstream, vertexNormals);
			}
			else if (line[1] == 't') {		// vt == 텍스쳐 좌표
				ReadVertexTexture(sstream, vertexTextureCoord);
			}
			else if (line[1] == ' ') {     // v == 정점 좌표
				ReadVertexNormal(sstream, vertexPositions);
			}
		}
		else if (line[0] == 'f') {         // 맨 앞 문자가 f이면 face(면)에 대한 정보이다
			ReadFace(sstream, indiciesVec);
		}
	}

	// 정점 노멀과 텍스쳐의 갯수가 각각 다 다르기 때문에 더이상 DrawElements를 사용하기는 어려움
	// 따라서 정점들을 복제함
	m_verticies.resize(indiciesVec[0].size());
	auto endLoop{ m_verticies.size() };

	for (auto i = 0; i < endLoop; ++i) {
		m_verticies[i].position = vertexPositions[indiciesVec[0][i]];
		if (!indiciesVec[1].empty()) m_verticies[i].texture = vertexTextureCoord[indiciesVec[1][i]];
		if (!indiciesVec[2].empty()) m_verticies[i].normal = vertexNormals[indiciesVec[2][i]];
	}

	std::cout << m_verticies.size() << std::endl;

	// 단 정점 최소 최댓값의 계산을 빠르게 하기위해 중복되지 않은 정점 배열을 계산에 사용
	m_noDuplicatedVertex = vertexPositions;

	CalcMinMaxVertexElem();
	MakeBoundingBox();
}

void Model::SetPatchParameters(int numOfPatches) {
	m_graphicsBuffer->SetPatchParameters(numOfPatches);
}

void Model::SetDrawMode(int drawMode) {
	m_graphicsBuffer->SetDrawMode(drawMode);
}

bool Model::ExistTexture() const {
	return bool{ m_textureComponent };
}

void Model::BindingTexture(int textureIndex) {
	m_textureComponent->BindingTexture(textureIndex);
}

void Model::Init() {
	m_graphicsBuffer = std::make_unique<GraphicBuffers>();
	m_graphicsBuffer->Init();

	m_graphicsBuffer->SetVerticies(m_verticies);
}

void Model::Update() {
}

void Model::Render() {
	m_graphicsBuffer->Render();
}
