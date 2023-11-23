#include "pch.h"
#include "Terrain.h"
#include "TextureComponent.h"

Terrain::Terrain(const glm::uvec2& mapSize) : m_terrainMapSize{ mapSize } {
	// 먼저 하이트맵의 텍스쳐를 불러옴
	m_heightMap = std::make_unique<TextureComponent>(".\\Textures\\terrain_height_map.png");
	auto textureID = m_heightMap->GetTextureID();
	auto textureImgInfo = m_heightMap->GetTextureInfo();

	m_heightMapImgWidth = textureImgInfo.x;
	m_heightMapImgHeight = textureImgInfo.y;

	CreateTerrainMeshMap();
	CreateTerrainVertexBuffers();
}

Terrain::~Terrain() { }

void Terrain::CreateTerrainMeshMap() {
	float tileWidth = m_heightMapImgWidth / static_cast<float>(m_terrainMapSize.x);
	float tileHeight = m_heightMapImgHeight / static_cast<float>(m_terrainMapSize.y);
	float left = (-m_heightMapImgWidth / 2.f);
	float bottom = (-m_heightMapImgHeight / 2.f);
	// xz평면 상에 지형을 그려줄 큐브 메쉬들의 정점을 생성함
	for (unsigned int x = 0; x < m_terrainMapSize.x; ++x) {
		for (unsigned int z = 0; z < m_terrainMapSize.y; ++z) {
			// 중앙을 0,0으로 잡고 왼쪽에서 부터 오른쪽으로 만듬
			// 공식은 이미지 너비의 반을 hw, 높이의 반을 hh라 하면 
			// i는 타일맵 으로 생각할때 타일 맵의 번호
			// -hw + w * ((i + 1 or + 0) / mapSize) -> hw를 왼쪽 오른쪽이라 생각하면 각 타일의 너비 높이는 w / mapsize.x, h / mapsize.z 이므로
			// left + (x * (w / mapsize.x), bottom + (z * (h / mapsize.z))
			// xz평면 상에 생성할 것이므로 y좌표는 항상 0
			// 텍스쳐 좌표는 정규화된 좌표이므로 0,1 사이에 존재해야함 따라서 
			// u,v = x / mapsize.x, z / mapsize.z
			Vertex leftTop{
				glm::vec3{
					left + static_cast<float>(x * tileWidth),
					0.f,
					bottom + static_cast<float>((z + 1) * tileHeight)
				},
				glm::vec2{
					static_cast<float>(x) / m_terrainMapSize.x, static_cast<float>(z + 1) / m_terrainMapSize.y
				},
				glm::vec3{ },
			};
			m_verticies.push_back(leftTop);

			Vertex leftBottom{
				glm::vec3{
					left + static_cast<float>(x * tileWidth),
					0.f,
					bottom + static_cast<float>((z * tileHeight))
				},
				glm::vec2{
					static_cast<float>(x) / m_terrainMapSize.x, static_cast<float>(z) / m_terrainMapSize.y
				},
				glm::vec3{ },
			};
			m_verticies.push_back(leftBottom);

			Vertex rightTop{
				glm::vec3{
					left + static_cast<float>(((x + 1) * tileWidth)),
					0.f,
					bottom + static_cast<float>((z + 1) * tileHeight)
				},
				glm::vec2{
					static_cast<float>(x + 1) / m_terrainMapSize.x, static_cast<float>(z + 1) / m_terrainMapSize.y
				},
				glm::vec3{ },
			};
			m_verticies.push_back(rightTop);

			Vertex rightBottom{
				glm::vec3{
					left + static_cast<float>((x + 1) * tileWidth),
					0.f,
					bottom + static_cast<float>(z * tileHeight)
				},
				glm::vec2{
					static_cast<float>(x) / m_terrainMapSize.x, static_cast<float>(z) / m_terrainMapSize.y
				},
				glm::vec3{ },
			};
			m_verticies.push_back(rightBottom);
		}
	}
}

void Terrain::CreateTerrainVertexBuffers() {
	// 지형을 그릴 VAO, VBO생성 및 정점 바인딩
	glGenBuffers(1, &m_terrainVBO);
	glGenVertexArrays(1, &m_terrainVAO);

	glBindVertexArray(m_terrainVAO);
	glBindBuffer(GL_VERTEX_ARRAY, m_terrainVBO);

	glBufferData(GL_ARRAY_BUFFER, uint32(m_verticies.size()) * sizeof(Vertex), &m_verticies[0], GL_STATIC_DRAW);

	// location 0번에 Vertex객체의 position정보를 넘겨줌
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// location 1번에 Vertex객체의 texture정보를 넘겨줌
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));
	glEnableVertexAttribArray(1);

	// location 2번에 Vertex객체의 normal정보를 넘겨줌
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);

	// 사각형 패치로 넘겨줌
	glPatchParameteri(GL_PATCH_VERTICES, 4);
}

void Terrain::Render() {
	glBindVertexArray(m_terrainVAO);
	glDrawArrays(GL_PATCHES, 0, uint32(m_verticies.size()));
	glBindVertexArray(0);
}
