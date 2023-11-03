#include "pch.h"
#include "LightObject.h"
#include "Model/Model.h"
#include "Model/ModelList.h"
#include "Graphics/Shader.h"

LightObject::LightObject() {
	m_modelTag = "cube";
	m_model = MODELLIST->GetModel("cube");


	m_lightColor = glm::vec3{ 1.f };
	m_objectColor = glm::vec3{ 1.f };
	m_scaleFactor = glm::vec3{ };

	m_position = { 0.f, 4.f, 0.f };
}

LightObject::~LightObject() { }

void LightObject::SetLightOption() {
	glm::vec3 diffuseColor{ m_lightColor * m_lightOption.diffuse };
	glm::vec3 ambientColor{ diffuseColor * m_lightOption.ambient };

	SHADER->SetUniformVec3("light.position", m_lightOption.position);
	SHADER->SetUniformVec3("light.ambient", ambientColor);
	SHADER->SetUniformVec3("light.diffuse", diffuseColor);
	SHADER->SetUniformVec3("light.specular", m_lightOption.specular);
}

void LightObject::Update(float deltaTime) {
	static float angle = 0.f;
	// ¿ø¿îµ¿ 
	m_position.x = 3 * std::cosf(glm::radians(angle));
	m_position.z = 3 * std::sinf(glm::radians(angle));

	angle += 0.01f;

	if (angle > 360.f) {
		angle = 0.f;
	}

	m_lightOption.position = m_position;
}

void LightObject::Render() {
	Object::Render();
}
