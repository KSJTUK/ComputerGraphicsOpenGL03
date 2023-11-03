#include "pch.h"
#include "Object/Object.h"
#include "Graphics/Shader.h"
#include "Model/Model.h"

Object::Object() { }

Object::~Object() { }

void Object::SetMeterials() {
	SHADER->SetUniformVec3("meterials.ambient", m_meterial.ambient);
	SHADER->SetUniformVec3("meterials.diffuse", m_meterial.diffuse);
	SHADER->SetUniformVec3("meterials.specular", m_meterial.specular);
	SHADER->SetUniformFloat("meterials.shininess", m_meterial.shininess);
}

void Object::Render() {
	glm::mat4 unit{ 1.f };

	glm::vec3 ypr{ glm::radians(m_rotateAngle) };

	glm::mat4 scaleMat = glm::scale(unit, m_scaleFactor);
	glm::mat4 rotateMat = glm::yawPitchRoll(ypr.y, ypr.x, ypr.z);
	glm::mat4 translateMat = glm::translate(unit, m_position);

	m_transform = translateMat * rotateMat * scaleMat;

	m_meterial.ambient = m_objectColor;
	m_meterial.diffuse = m_objectColor;

	SetMeterials();

	m_model->SetInitTransformMat(m_initTransform);
	m_model->SetTransformMat(m_transform);
	m_model->SetParentModelTransformMat(m_parentTransform);

	m_model->Render();
}
