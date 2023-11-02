#include "pch.h"
#include "Object/Object.h"
#include "Graphics/Shader.h"
#include "Model/Model.h"

Object::Object() { }

Object::~Object() { }

void Object::Render() {
	glm::mat4 unit{ 1.f };

	glm::vec3 ypr{ glm::radians(m_rotateAngle) };

	glm::mat4 scaleMat = glm::scale(unit, m_scaleFactor);
	glm::mat4 rotateMat = glm::yawPitchRoll(ypr.y, ypr.x, ypr.z);
	glm::mat4 translateMat = glm::translate(unit, m_position);

	m_transform = translateMat * rotateMat * scaleMat;

	m_model->SetInitTransformMat(m_initTransform);
	m_model->SetTransformMat(m_transform);
	m_model->SetParentModelTransformMat(m_parentTransform);

	m_model->Render();
}
