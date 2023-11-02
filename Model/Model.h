#pragma once

class Model {
public:
	Model(const std::string& objectFilePath);
	~Model();

	Model(const Model& other) = delete;
	Model& operator=(const Model& other) = delete;

private:
	// VAO, VBO, EBO를 가지는 객체
	std::unique_ptr<class GraphicBuffers> m_graphicsBuffer{ };

	// 정점 속성들을 저장할 vector
	std::vector<Vertex> m_verticies{ };

	// 정점 노멀들을 저장할 vector
	std::vector<glm::vec3> m_vertexNormals{ };
	std::vector<glm::vec3> m_noDuplicatedVertex{ };

	// 정점좌표들 중 최대 최소인 x, y, z 값을 저장할 변수들
	glm::vec3 m_maxCoord{ };
	glm::vec3 m_minCoord{ };

	std::pair<glm::vec3, glm::vec3> m_boundingBox{ };

	glm::mat4 m_modelInitTransform{ 1.f };
	glm::mat4 m_modelTransform{ 1.f };
	glm::mat4 m_modelParentTransform{ 1.f };

private:
	void CalcMinMaxVertexElem();
	void MakeBoundingBox();

private:
	void ReadFace(std::stringstream& contents, std::vector<unsigned int>* indiciesVec);
	void ReadVertex(std::stringstream& contents, uint32& vertexCount);
	void ReadVertex(std::stringstream& contents, std::vector<glm::vec3>& positions);
	void ReadVertexTexture(std::stringstream& contents, uint32& txtureCount);
	void ReadVertexTexture(std::stringstream& contents, std::vector<glm::vec2>& textureCoords);
	void ReadVertexNormal(std::stringstream& contents, uint32& normalCount);
	void ReadVertexNormal(std::stringstream& contents, std::vector<glm::vec3>& normals);

	void ReadObject(const char* filePath);

public:
	glm::mat4 GetModelTransformMat() const;

	// setter
	void SetDrawMode(int drawMode);

	void SetInitTransformMat(const glm::mat4& initTarnsformMat);
	void SetTransformMat(const glm::mat4& transformMat);
	void SetParentModelTransformMat(const glm::mat4& parentTransformMat);

	std::pair<glm::vec3, glm::vec3> GetBoundingBox() const { return m_boundingBox; }

public:
	void Init();
	void Update();
	void Render();
};