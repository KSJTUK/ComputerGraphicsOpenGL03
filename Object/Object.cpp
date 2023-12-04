#include "pch.h"
#include "Object/Object.h"
#include "Graphics/Shader.h"
#include "Model/Model.h"
#include "Model/ModelList.h"

Object::Object() { }

Object::Object(const std::string& modelTag) : m_modelTag{ modelTag } {
	m_model = MODELLIST->GetModel(modelTag);
}

Object::Object(const std::string& modelTag, const glm::vec3& objectColor) : m_modelTag{ modelTag }, m_objectColor{ objectColor } {
	m_model = MODELLIST->GetModel(modelTag);
}

Object::~Object() { }

void Object::SetMeterials() {
	OBJECTSHADER->SetUniformVec3("objectColor", m_objectColor);
	OBJECTSHADER->SetUniformInt("meterials.diffuse", 0);
	OBJECTSHADER->SetUniformVec3("meterials.specular", m_meterial.specular);
	OBJECTSHADER->SetUniformFloat("meterials.shininess", m_meterial.shininess);
}

bool Object::ExistTexture() const {
	return m_model->ExistTexture();
}

void Object::SetObjectColor(const glm::vec3& color) {
	m_objectColor = color;
}