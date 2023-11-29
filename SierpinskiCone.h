#pragma once

class SierpinskiCone {
public:
	SierpinskiCone(const std::string& objectFilePath);
	SierpinskiCone(const std::string& objectFilePath, const std::string& textureFilePath);
	~SierpinskiCone();

	SierpinskiCone(const SierpinskiCone& other) = delete;
	SierpinskiCone& operator=(const SierpinskiCone& other) = delete;

private:
	// VAO, VBO, EBO�� ������ ��ü
	std::unique_ptr<class GraphicBuffers> m_graphicsBuffer{ };
	std::unique_ptr<class TextureComponent> m_textureComponent{ };

	// ���� �Ӽ����� ������ vector
	std::vector<Vertex> m_originVerticies{ };
	std::vector<Vertex> m_verticies{ };
	std::vector<Vertex> m_tempVertex{ };

	// ���� ��ֵ��� ������ vector
	std::vector<glm::vec3> m_vertexNormals{ };
	std::vector<glm::vec3> m_noDuplicatedVertex{ };

	// ������ǥ�� �� �ִ� �ּ��� x, y, z ���� ������ ������
	glm::vec3 m_maxCoord{ };
	glm::vec3 m_minCoord{ };

	std::pair<glm::vec3, glm::vec3> m_boundingBox{ };

	glm::vec3 m_objectColor{ 0.f, 1.f, 0.f };
	Meterial m_meterial{ };

private:
	void CalcMinMaxVertexElem();
	void MakeBoundingBox();

private:
	void ReadFace(std::stringstream& contents, std::vector<unsigned int>* indiciesVec);
	void ReadVertex(std::stringstream& contents, std::vector<glm::vec3>& positions);
	void ReadVertexTexture(std::stringstream& contents, std::vector<glm::vec2>& textureCoords);
	void ReadVertexNormal(std::stringstream& contents, std::vector<glm::vec3>& normals);

	void ReadObject(const char* filePath);

	Vertex GetMid(const Vertex& a, const Vertex& b);


	void SetMeterials() const;
	void CreateSierpinski(const int& level, int recursionDepth=0);

public:
	// setter
	void SetColor(const glm::vec3& color);
	void SetPatchParameters(int numOfPatches);
	void SetDrawMode(int drawMode);
	bool ExistTexture() const;

	std::pair<glm::vec3, glm::vec3> GetBoundingBox() const { return m_boundingBox; }

public:
	void Init();
	void Update();
	void Render();
};