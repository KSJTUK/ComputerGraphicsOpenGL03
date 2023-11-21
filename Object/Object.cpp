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
	SHADER->SetUniformVec3("objectColor", m_objectColor);
	SHADER->SetUniformInt("meterials.diffuse", 0);
	SHADER->SetUniformVec3("meterials.specular", m_meterial.specular);
	SHADER->SetUniformFloat("meterials.shininess", m_meterial.shininess);
}

bool Object::ExistTexture() const {
	return m_model->ExistTexture();
}

void Object::SetObjectColor(const glm::vec3& color) {
	m_objectColor = color;
}

void Object::Render() {
	glm::mat4 unit{ 1.f };

	glm::vec3 ypr{ glm::radians(m_rotateAngle) };

	glm::mat4 scaleMat = glm::scale(unit, m_scaleFactor);
	glm::mat4 rotateMat = glm::yawPitchRoll(ypr.y, ypr.x, ypr.z);
	glm::mat4 translateMat = glm::translate(unit, m_position);

	m_transform = translateMat * rotateMat * scaleMat;

	SetMeterials();

	SHADER->SetUniformMat4("modelInitTransform", m_initTransform);
	SHADER->SetUniformMat4("modelTransform", m_transform);
	SHADER->SetUniformMat4("modelsParentTransform", m_parentTransform);

	m_model->SetDrawMode(GL_PATCHES);

	m_model->Render();
}
