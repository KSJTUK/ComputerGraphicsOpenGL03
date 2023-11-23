#pragma once

class Terrain {
public:
	Terrain(const glm::uvec2& mapSize);
	~Terrain();

private:
	glm::uvec2 m_terrainMapSize{ };
	std::vector<Vertex> m_verticies{ };

	unsigned int m_terrainVAO{ };
	unsigned int m_terrainVBO{ };

	std::unique_ptr<class TextureComponent> m_heightMap{ };

	unsigned int m_textureID{ };
	int32 m_heightMapImgWidth{ };
	int32 m_heightMapImgHeight{ };

	std::unique_ptr<class GraphicBuffers> m_vertexBuffer{ };

private:
	void CreateTerrainMeshMap();
	void CreateTerrainVertexBuffers();

public:
	void Init();
	void Update(float deltaTime);
	void Render();

};