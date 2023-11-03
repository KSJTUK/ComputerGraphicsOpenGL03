#include "pch.h"
#include "LightObject.h"
#include "Model/Model.h"
#include "Model/ModelList.h"
#include "Graphics/Shader.h"

LightObject::LightObject() {
	m_modelTag = "sphere";
	m_model = MODELLIST->GetModel("sphere");


	m_lightColor = glm::vec3{ 1.f };
	m_objectColor = glm::vec3{ 1.f };
	m_scaleFactor = glm::vec3{ 0.3f };
	m_meterial.ambient = glm::vec3{ 1.f };
	m_meterial.diffuse = glm::vec3{ 1.f };
	m_meterial.specular = glm::vec3{ 1.f };

	m_position = { 0.f, 2.f, 0.f };
}

LightObject::LightObject(const std::string& modelTag) {
	m_modelTag = modelTag;
	m_model = MODELLIST->GetModel(m_modelTag);


	m_lightColor = glm::vec3{ 1.f };
	m_objectColor = glm::vec3{ 1.f };
}

LightObject::LightObject(const std::string& modelTag, const glm::vec3& lightColor) {
	m_modelTag = modelTag;
	m_model = MODELLIST->GetModel(m_modelTag);


	m_lightColor = lightColor;
	m_objectColor = lightColor;
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
	static float lightChangedAngle = 0.f;

	static float lightDir{ 1.f };

	// ¿ø¿îµ¿ 
	m_position.x = 10.f * std::cosf(glm::radians(angle));
	m_position.z = 10.f * std::sinf(glm::radians(angle));

	m_lightColor = glm::vec3{ std::cosf(glm::radians(lightChangedAngle)) };

	lightChangedAngle += 10.f * lightDir * deltaTime;

	if (lightChangedAngle >= 90.f) {
		lightChangedAngle = 90.f;
		lightDir = -1.f;
	}
	else if (lightChangedAngle <= -90.f) {
		lightChangedAngle = -90.f;
		lightDir = 1.f;
	}

	angle += 10.f * deltaTime;

	if (angle > 360.f) {
		angle = 0.f;
	}

	m_lightOption.position = m_position;
}

void LightObject::Render() {
	LIGHTOBJECTSHADER->SetUniformVec3("objectColor", m_lightColor);

	glm::mat4 unit{ 1.f };
	glm::vec3 ypr{ glm::radians(m_rotateAngle) };

	glm::mat4 scaleMat = glm::scale(unit, m_scaleFactor);
	glm::mat4 rotateMat = glm::yawPitchRoll(ypr.y, ypr.x, ypr.z);
	glm::mat4 translateMat = glm::translate(unit, m_position);

	m_transform = translateMat * rotateMat * scaleMat;

	LIGHTOBJECTSHADER->SetUniformMat4("initTransform", m_initTransform);
	LIGHTOBJECTSHADER->SetUniformMat4("modelTransform", m_transform);
	LIGHTOBJECTSHADER->SetUniformMat4("parentTransform", m_parentTransform);

	m_model->Render();
}
