#include "pch.h"
#include "Cube.h"
#include "Graphics/Shader.h"
#include "Graphics/GraphicBuffers.h"
#include "Util/TextureComponent.h"
#include "Model/Model.h"
#include "Model/ModelList.h"

Cube::Cube() : Object{ "earth" } {

}

Cube::Cube(const std::string& modelTag) : Object{ modelTag } {
	m_terrainOffset = 0.75f;
}

Cube::Cube(const std::string& modelTag, const glm::mat4& initTransform) : Object{ modelTag } {
	m_initTransform = initTransform;
}

Cube::~Cube() { }

void Cube::SetOrbitAxis(const glm::vec3& axis) {
	m_orbitAxis = axis;
}

void Cube::Orbit() {
	m_position = glm::rotate(m_position, glm::radians(0.01f), m_orbitAxis);
}

void Cube::SetTransform() {
	glm::mat4 unit{ 1.f };

	glm::vec3 ypr{ glm::radians(m_rotateAngle) };

	glm::mat4 scaleMat = glm::scale(unit, m_scaleFactor);
	glm::mat4 rotateMat = glm::yawPitchRoll(ypr.y, ypr.x, ypr.z);
	glm::mat4 translateMat = glm::translate(unit, m_position);

	m_transform = translateMat * rotateMat * scaleMat;

	OBJECTSHADER->SetUniformMat4("modelInitTransform", m_initTransform);
	OBJECTSHADER->SetUniformMat4("modelTransform", m_transform);
	OBJECTSHADER->SetUniformMat4("modelsParentTransform", m_parentTransform);
}

void Cube::BindingTexture() {
	if (m_model->ExistTexture()) {
		m_model->BindingTexture(0);
		OBJECTSHADER->SetUniformBool("notextureID", false);
	}
	else {
		OBJECTSHADER->SetUniformBool("notextureID", true);
	}
}

void Cube::AlphaBlending() {
	m_blending = true;
}

void Cube::Update(float deltaTime) {
	static float angle = 0.f;
	static float rotateAngle = 0.f;

	if (m_orbit) {
		Orbit();
	}

	if (m_rotate) {
		m_rotateAngle.y += angleSpeed * deltaTime;
		if (m_rotateAngle.y > 360.f) {
			m_rotateAngle.y = 0.f;
		}
	}
}

void Cube::Render() {
	SetMeterials();
	SetTransform();
	BindingTexture();

	OBJECTSHADER->UseProgram();

	if (m_blending) {
		glDisable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	m_model->SetDrawMode(GL_TRIANGLES);
	m_model->Render();

	if (m_blending) {
		glDisable(GL_BLEND);
		glEnable(GL_CULL_FACE);
	}

	OBJECTSHADER->UnUseProgram();
}

TexturedCube::TexturedCube() {
	OBJECTSHADER->UseProgram();

	m_vertexData = {
		{
		Vertex{ glm::vec3{ -0.5f, -0.5f, -0.5f }, glm::vec2{ 0.0f,  0.0f}, glm::vec3{ 0.0f,  0.0f, -1.0f } },
		Vertex{ glm::vec3{  0.5f, -0.5f, -0.5f }, glm::vec2{ 1.0f,  0.0f}, glm::vec3{ 0.0f,  0.0f, -1.0f } },
		Vertex{ glm::vec3{  0.5f,  0.5f, -0.5f }, glm::vec2{ 1.0f,  1.0f}, glm::vec3{ 0.0f,  0.0f, -1.0f } },
		Vertex{ glm::vec3{  0.5f,  0.5f, -0.5f }, glm::vec2{ 1.0f,  1.0f}, glm::vec3{ 0.0f,  0.0f, -1.0f } },
		Vertex{ glm::vec3{ -0.5f,  0.5f, -0.5f }, glm::vec2{ 0.0f,  1.0f}, glm::vec3{ 0.0f,  0.0f, -1.0f } },
		Vertex{ glm::vec3{ -0.5f, -0.5f, -0.5f }, glm::vec2{ 0.0f,  0.0f}, glm::vec3{ 0.0f,  0.0f, -1.0f } },
		},
		{
		Vertex{ glm::vec3{ -0.5f, -0.5f,  0.5f }, glm::vec2{ 0.0f,  0.0f }, glm::vec3{ 0.0f,  0.0f,  1.0f } },
		Vertex{ glm::vec3{  0.5f, -0.5f,  0.5f }, glm::vec2{ 1.0f,  0.0f }, glm::vec3{ 0.0f,  0.0f,  1.0f } },
		Vertex{ glm::vec3{  0.5f,  0.5f,  0.5f }, glm::vec2{ 1.0f,  1.0f }, glm::vec3{ 0.0f,  0.0f,  1.0f } },
		Vertex{ glm::vec3{  0.5f,  0.5f,  0.5f }, glm::vec2{ 1.0f,  1.0f }, glm::vec3{ 0.0f,  0.0f,  1.0f } },
		Vertex{ glm::vec3{ -0.5f,  0.5f,  0.5f }, glm::vec2{ 0.0f,  1.0f }, glm::vec3{ 0.0f,  0.0f,  1.0f } },
		Vertex{ glm::vec3{ -0.5f, -0.5f,  0.5f }, glm::vec2{ 0.0f,  0.0f }, glm::vec3{ 0.0f,  0.0f,  1.0f } },
		},
		{
		Vertex{ glm::vec3{ -0.5f,  0.5f,  0.5f }, glm::vec2{ 1.0f,  0.0f }, glm::vec3{ -1.0f,  0.0f,  0.0f } },
		Vertex{ glm::vec3{ -0.5f,  0.5f, -0.5f }, glm::vec2{ 1.0f,  1.0f }, glm::vec3{ -1.0f,  0.0f,  0.0f } },
		Vertex{ glm::vec3{ -0.5f, -0.5f, -0.5f }, glm::vec2{ 0.0f,  1.0f }, glm::vec3{ -1.0f,  0.0f,  0.0f } },
		Vertex{ glm::vec3{ -0.5f, -0.5f, -0.5f }, glm::vec2{ 0.0f,  1.0f }, glm::vec3{ -1.0f,  0.0f,  0.0f } },
		Vertex{ glm::vec3{ -0.5f, -0.5f,  0.5f }, glm::vec2{ 0.0f,  0.0f }, glm::vec3{ -1.0f,  0.0f,  0.0f } },
		Vertex{ glm::vec3{ -0.5f,  0.5f,  0.5f }, glm::vec2{ 1.0f,  0.0f }, glm::vec3{ -1.0f,  0.0f,  0.0f } },
		},
		{
		Vertex{ glm::vec3{ 0.5f,  0.5f,  0.5f }, glm::vec2{ 1.0f,  0.0f } , glm::vec3{ 1.0f,  0.0f,  0.0f } },
		Vertex{ glm::vec3{ 0.5f,  0.5f, -0.5f }, glm::vec2{ 1.0f,  1.0f } , glm::vec3{ 1.0f,  0.0f,  0.0f } },
		Vertex{ glm::vec3{ 0.5f, -0.5f, -0.5f }, glm::vec2{ 0.0f,  1.0f } , glm::vec3{ 1.0f,  0.0f,  0.0f } },
		Vertex{ glm::vec3{ 0.5f, -0.5f, -0.5f }, glm::vec2{ 0.0f,  1.0f } , glm::vec3{ 1.0f,  0.0f,  0.0f } },
		Vertex{ glm::vec3{ 0.5f, -0.5f,  0.5f }, glm::vec2{ 0.0f,  0.0f } , glm::vec3{ 1.0f,  0.0f,  0.0f } },
		Vertex{ glm::vec3{ 0.5f,  0.5f,  0.5f }, glm::vec2{ 1.0f,  0.0f } , glm::vec3{ 1.0f,  0.0f,  0.0f } },
		},
		{
		Vertex{ glm::vec3{ -0.5f, -0.5f, -0.5f }, glm::vec2{ 0.0f,  1.0f }, glm::vec3{ 0.0f, -1.0f,  0.0f } },
		Vertex{ glm::vec3{  0.5f, -0.5f, -0.5f }, glm::vec2{ 1.0f,  1.0f }, glm::vec3{ 0.0f, -1.0f,  0.0f } },
		Vertex{ glm::vec3{  0.5f, -0.5f,  0.5f }, glm::vec2{ 1.0f,  0.0f }, glm::vec3{ 0.0f, -1.0f,  0.0f } },
		Vertex{ glm::vec3{  0.5f, -0.5f,  0.5f }, glm::vec2{ 1.0f,  0.0f }, glm::vec3{ 0.0f, -1.0f,  0.0f } },
		Vertex{ glm::vec3{ -0.5f, -0.5f,  0.5f }, glm::vec2{ 0.0f,  0.0f }, glm::vec3{ 0.0f, -1.0f,  0.0f } },
		Vertex{ glm::vec3{ -0.5f, -0.5f, -0.5f }, glm::vec2{ 0.0f,  1.0f }, glm::vec3{ 0.0f, -1.0f,  0.0f } },
		},
		{
		Vertex{ glm::vec3{ -0.5f,  0.5f, -0.5f }, glm::vec2{ 0.0f,  1.0f }, glm::vec3{ 0.0f,  1.0f,  0.0f } },
		Vertex{ glm::vec3{  0.5f,  0.5f, -0.5f }, glm::vec2{ 1.0f,  1.0f }, glm::vec3{ 0.0f,  1.0f,  0.0f } },
		Vertex{ glm::vec3{  0.5f,  0.5f,  0.5f }, glm::vec2{ 1.0f,  0.0f }, glm::vec3{ 0.0f,  1.0f,  0.0f } },
		Vertex{ glm::vec3{  0.5f,  0.5f,  0.5f }, glm::vec2{ 1.0f,  0.0f }, glm::vec3{ 0.0f,  1.0f,  0.0f } },
		Vertex{ glm::vec3{ -0.5f,  0.5f,  0.5f }, glm::vec2{ 0.0f,  0.0f }, glm::vec3{ 0.0f,  1.0f,  0.0f } },
		Vertex{ glm::vec3{ -0.5f,  0.5f, -0.5f }, glm::vec2{ 0.0f,  1.0f }, glm::vec3{ 0.0f,  1.0f,  0.0f } }
		}
	};

	std::string dir = "./textures/";
	std::string path[6]{
		"left.png", "right.png",
		"top.png", "bottom.png",
		"front.png", "back.png"
	};

	auto faceSize = m_vertexData.size();
	m_graphicBuffers.resize(faceSize);
	m_textures.resize(faceSize);
	for (auto i = 0; i < faceSize; ++i) {
		m_graphicBuffers[i] = std::make_unique<GraphicBuffers>();
		m_graphicBuffers[i]->Init();
		m_graphicBuffers[i]->SetVerticies(m_vertexData[i]);
		m_graphicBuffers[i]->SetDrawMode(GL_TRIANGLES);
		
		m_textures[i] = std::make_unique<TextureComponent>();
		m_textures[i]->LoadTexture(dir + path[i], false);
	}

	OBJECTSHADER->UnUseProgram();
}

TexturedCube::~TexturedCube() {

}

void TexturedCube::Update(float deltaTime) {
	
}

void TexturedCube::Render() {
	OBJECTSHADER->SetUniformVec4("objectColor", glm::vec4{ 1.f });
	OBJECTSHADER->SetUniformVec3("meterials.specular", glm::vec3{ 1.f });
	OBJECTSHADER->SetUniformFloat("meterials.shininess", 32.f);

	OBJECTSHADER->SetUniformMat4("modelsParentTransform", glm::mat4{ 1.f });
	OBJECTSHADER->SetUniformMat4("modelInitTransform", glm::mat4{ 1.f });
	OBJECTSHADER->SetUniformMat4("modelTransform", glm::translate(glm::mat4{ 1.f }, glm::vec3{ 0.f, 10.f, -5.f }));
	OBJECTSHADER->SetUniformInt("meterials.diffuse", 0);
	OBJECTSHADER->SetUniformBool("notextureID", false);

	OBJECTSHADER->UseProgram();

	glDisable(GL_CULL_FACE);
	auto faceSize = m_vertexData.size();
	for (auto i = 0; i < faceSize; ++i) {
		m_textures[i]->BindingTextures();
		m_graphicBuffers[i]->Render();
	}

	glEnable(GL_CULL_FACE);
	OBJECTSHADER->UnUseProgram();
}
