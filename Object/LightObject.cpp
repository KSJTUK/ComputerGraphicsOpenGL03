#include "pch.h"
#include "LightObject.h"
#include "Model/Model.h"
#include "Model/ModelList.h"
#include "Graphics/Shader.h"

LightObject::LightObject() {
	m_modelTag = "cube";
	m_model = MODELLIST->GetModel("cube");


	m_objectColor = glm::vec3{ 1.f };
	m_lightColor = glm::vec3{ 1.f };
	SHADER->SetUniformVec3("lightColor", m_lightColor);

	m_position = { 3.f, 2.f, 0.f };
}

LightObject::~LightObject() { }

void LightObject::Update(float deltaTime) { }

void LightObject::Render() {
	SHADER->SetUniformVec3("lightObjectPosition", glm::vec3{ 0.f, 3.f, 0.f });
	Object::Render();
}
