#include "pch.h"
#include "Terrain.h"
#include "Graphics/GraphicBuffers.h"
#include "TextureComponent.h"
#include "Graphics/Shader.h"

Terrain::Terrain(const glm::uvec2& mapSize) : m_terrainMapSize{ mapSize } {
	// ���� ����Ʈ���� �ؽ��ĸ� �ҷ���
	m_heightMap = std::make_unique<TextureComponent>(".\\textures\\height.png", GL_RGBA);
	m_textureID = m_heightMap->GetTextureID();
	auto textureImgInfo = m_heightMap->GetTextureInfo();

	m_heightMapImgWidth = textureImgInfo.x;
	m_heightMapImgHeight = textureImgInfo.y;

	m_vertexBuffer = std::make_unique<GraphicBuffers>();
	m_vertexBuffer->Init();

	CreateTerrainMeshMap();
	//CreateTerrainVertexBuffers();
	m_vertexBuffer->SetVerticies(m_verticies);
}

Terrain::~Terrain() { }

void Terrain::CreateTerrainMeshMap() {
	float tileWidth = m_heightMapImgWidth / static_cast<float>(m_terrainMapSize.x);
	float tileHeight = m_heightMapImgHeight / static_cast<float>(m_terrainMapSize.y);
	float left = (-m_heightMapImgWidth / 2.f);
	float bottom = (-m_heightMapImgHeight / 2.f);
	glm::vec3 terrainNorm{ 0.f, 1.f, 0.f };
	// xz��� �� ������ �׷��� ť�� �޽����� ������ ������
	for (unsigned int x = 0; x < m_terrainMapSize.x; ++x) {
		for (unsigned int z = 0; z < m_terrainMapSize.y; ++z) {
			// �߾��� 0,0���� ��� ���ʿ��� ���� ���������� ����
			// ������ �̹��� �ʺ��� ���� hw, ������ ���� hh�� �ϸ� 
			// i�� Ÿ�ϸ� ���� �����Ҷ� Ÿ�� ���� ��ȣ
			// -hw + w * ((i + 1 or + 0) / mapSize) -> hw�� ���� �������̶� �����ϸ� �� Ÿ���� �ʺ� ���̴� w / mapsize.x, h / mapsize.z �̹Ƿ�
			// left + (x * (w / mapsize.x), bottom + (z * (h / mapsize.z))
			// xz��� �� ������ ���̹Ƿ� y��ǥ�� �׻� 0
			// �ؽ��� ��ǥ�� ����ȭ�� ��ǥ�̹Ƿ� 0,1 ���̿� �����ؾ��� ���� 
			// u,v = x / mapsize.x, z / mapsize.z
			Vertex p0{
				glm::vec3{
					left + static_cast<float>(x * tileWidth),
					0.f,
					bottom + static_cast<float>(z * tileHeight)
				},
				glm::vec2{
					static_cast<float>(x) / m_terrainMapSize.x, static_cast<float>(z) / m_terrainMapSize.y
				},
				terrainNorm
			};

			Vertex p1{
				glm::vec3{
					left + static_cast<float>((x + 1) * tileWidth),
					0.f,
					bottom + static_cast<float>((z * tileHeight))
				},
				glm::vec2{
					static_cast<float>(x + 1) / m_terrainMapSize.x, static_cast<float>(z) / m_terrainMapSize.y
				},
				terrainNorm
			};

			Vertex p2{
				glm::vec3{
					left + static_cast<float>(x * tileWidth),
					0.f,
					bottom + static_cast<float>((z + 1) * tileHeight)
				},
				glm::vec2{
					static_cast<float>(x) / m_terrainMapSize.x, static_cast<float>(z + 1) / m_terrainMapSize.y
				},
				terrainNorm
			};

			Vertex p3{
				glm::vec3{
					left + static_cast<float>((x + 1) * tileWidth),
					0.f,
					bottom + static_cast<float>((z + 1) * tileHeight)
				},
				glm::vec2{
					static_cast<float>(x + 1) / m_terrainMapSize.x, static_cast<float>(z + 1) / m_terrainMapSize.y
				},
				terrainNorm
			};

			m_verticies.push_back(p0);      // triangle 1
			m_verticies.push_back(p2);
			m_verticies.push_back(p1);
			m_verticies.push_back(p1);
			m_verticies.push_back(p2);
			m_verticies.push_back(p3);
		}
	}
}

void Terrain::CreateTerrainVertexBuffers() {
	TERRAINSHADER->UseProgram();

	// ������ �׸� VAO, VBO���� �� ���� ���ε�
	glBufferData(GL_ARRAY_BUFFER, uint32(m_verticies.size()) * sizeof(Vertex), &m_verticies[0], GL_STATIC_DRAW);

	// location 0���� Vertex��ü�� position������ �Ѱ���
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// location 1���� Vertex��ü�� texture������ �Ѱ���
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));
	glEnableVertexAttribArray(1);

	// location 2���� Vertex��ü�� normal������ �Ѱ���
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);

	// �簢�� ��ġ�� �Ѱ���
	glPatchParameteri(GL_PATCH_VERTICES, 3);

	TERRAINSHADER->UnUseProgram();
}

void Terrain::Init() {

}

void Terrain::Update(float deltaTime) {

}

void Terrain::Render() {
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, m_textureID);
	//TERRAINSHADER->SetUniformInt("heightMap", 0);
	//glBindVertexArray(m_terrainVAO);
	//glDrawArrays(GL_PATCHES, 0, uint32(m_verticies.size()));
	//glBindVertexArray(0);
	m_vertexBuffer->BindingTexture(m_textureID);
	m_vertexBuffer->SetDrawMode(GL_PATCHES);
	m_vertexBuffer->Render();
}
