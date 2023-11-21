#include "pch.h"
#include "LightObject.h"
#include "Model/Model.h"
#include "Model/ModelList.h"
#include "Graphics/Shader.h"

LightObject::LightObject() {
	m_lightColor = glm::vec3{ 1.f };
	m_objectColor = m_lightColor;
}

LightObject::LightObject(const std::string& modelTag) : Object{ modelTag } {
	m_lightColor = glm::vec3{ 1.f };
	m_objectColor = m_lightColor;
}

LightObject::LightObject(const std::string& modelTag, const glm::vec3& lightColor) : Object{ modelTag, lightColor }, m_lightColor{ lightColor } {
}

LightObject::~LightObject() { }

void LightObject::SetLightOption() {
	glm::vec3 diffuseColor{ m_lightColor * m_lightOption.diffuse };
	glm::vec3 ambientColor{ diffuseColor * m_lightOption.ambient };
	m_lightOption.specular = m_lightColor;

	// phong, point lighting
	SHADER->SetUniformVec3("light.position", m_lightOption.position);

	// Direction Lighting
	// SHADER->SetUniformVec3("light.direction", glm::vec3{ 0.f, -2.f, -1.f });
	SHADER->SetUniformVec3("light.ambient", ambientColor);
	SHADER->SetUniformVec3("light.diffuse", diffuseColor);
	SHADER->SetUniformVec3("light.specular", m_lightOption.specular);

	 //point, flash lightting
	SHADER->SetUniformFloat("light.constant", 1.0f);
	SHADER->SetUniformFloat("light.linear", 0.027f);
	SHADER->SetUniformFloat("light.quadratic", 0.0028f);
}

void LightObject::Update(float deltaTime) {
	//// 밝기 조절
	//static float lightChangedAngle = 0.f;
	//static float lightDir{ 1.f };

	//float maxColorRGB{ std::max({ m_lightColor.x, m_lightColor.y, m_lightColor.z }) };
	//float minColorRGB{ std::min({ m_lightColor.x, m_lightColor.y, m_lightColor.z }) };

	//m_lightColor += glm::vec3{ std::sinf(glm::radians(lightChangedAngle)) };

	//lightChangedAngle += 0.1f * lightDir * deltaTime;

	//if (maxColorRGB >= 1.f) {
	//	m_lightColor -= glm::vec3{ maxColorRGB - 1.f };
	//	lightDir = -1.f;
	//}
	//else if (maxColorRGB <= 0.f) {
	//	m_lightColor += glm::vec3{ -maxColorRGB };
	//	lightDir = 1.f;
	//}

	//// 원운동 
	//static float angle = 0.f;
	//static float radius = 10.f;

	//m_position.x = radius * std::cosf(glm::radians(angle));
	//m_position.z = radius * std::sinf(glm::radians(angle));
	//angle += radius * deltaTime;

	//if (angle > 360.f) {
	//	angle = 0.f;
	//}

	//m_lightOption.position = m_position;
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

	m_model->SetDrawMode(GL_TRIANGLES);

	m_model->Render();
}
