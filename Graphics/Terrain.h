#pragma once

enum TerrainTex {
	HEIGHT_MAP = 0,
	TERRAIN_TEX
};

class Terrain {
public:
	Terrain(const glm::uvec2& mapSize);
	~Terrain();

private:
	glm::uvec2 m_terrainMapSize{ };
	std::vector<Vertex> m_verticies{ };

	std::unique_ptr<class TextureComponent> m_textureComponent{ };

	std::unique_ptr<class GraphicBuffers> m_vertexBuffer{ };

	glm::uvec2 m_terrainScale{ };

	std::vector<std::vector<float>> m_textureHeight{ };
	const float m_yScale{ 64.f };
	const float m_yShift{ 64.f / 2.f };

private:
	void CreateTerrainMeshMap();
	void CreateTerrainVertexBuffers();

public:
	float GetHeight(const glm::vec3& position, float offset);
	void MoveHeightPosition(glm::vec3& position, float offset);

public:
	void Init();
	void Update(float deltaTime);
	void Render();

};