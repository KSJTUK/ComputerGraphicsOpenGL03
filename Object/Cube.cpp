#include "pch.h"
#include "Cube.h"
#include "Graphics/Shader.h"
#include "Model/Model.h"
#include "Model/ModelList.h"

Cube::Cube() : Object{ "earth" } {

}

Cube::Cube(const std::string& modelTag) : Object{ modelTag } {

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

	m_model->SetDrawMode(GL_TRIANGLES);
	m_model->Render();

	OBJECTSHADER->UnUseProgram();
}