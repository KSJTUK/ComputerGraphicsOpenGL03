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
	m_scaleFactor = glm::vec3{ };

	m_position = { 1.2f, 2.f, 1.f };
}

LightObject::~LightObject() { }

void LightObject::Update(float deltaTime) { }

void LightObject::Render() {
	Object::Render();
}
