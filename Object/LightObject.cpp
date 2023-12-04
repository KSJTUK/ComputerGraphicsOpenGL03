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

void LightObject::StartOnOff() {
	m_lightOnOff = true;
}

void LightObject::StopOnOff() {
	m_lightOnOff = false;
}

void LightObject::SetLightOption() {
	glm::vec3 diffuseColor{ m_lightColor * m_lightOption.diffuse };
	glm::vec3 ambientColor{ diffuseColor * m_lightOption.ambient };
	m_lightOption.specular = m_lightColor;

	// phong, point lighting
	OBJECTSHADER->SetUniformVec3("pointLight.position", m_lightOption.position);

	// Direction Lighting
	if (m_directionLightingOn) {
		OBJECTSHADER->SetUniformVec3("dirLight.direction", glm::vec3{ 0.f, -1.f, 0.f });
		OBJECTSHADER->SetUniformVec3("dirLight.ambient", ambientColor);
		OBJECTSHADER->SetUniformVec3("dirLight.diffuse", diffuseColor);
		OBJECTSHADER->SetUniformVec3("dirLight.specular", glm::vec3{ 0.f });
	}

	 //point, flash lightting
	OBJECTSHADER->SetUniformVec3("pointLight.ambient", ambientColor);
	OBJECTSHADER->SetUniformVec3("pointLight.diffuse", diffuseColor);
	OBJECTSHADER->SetUniformVec3("pointLight.specular", m_lightOption.specular);

	OBJECTSHADER->SetUniformFloat("pointLight.constant", 1.0f);
	OBJECTSHADER->SetUniformFloat("pointLight.linear", 0.027f);
	OBJECTSHADER->SetUniformFloat("pointLight.quadratic", 0.0028f);

	if (m_sportLightingOn) {
		OBJECTSHADER->SetUniformVec3("spotLight.ambient", ambientColor);
		OBJECTSHADER->SetUniformVec3("spotLight.diffuse", diffuseColor);
		OBJECTSHADER->SetUniformVec3("spotLight.specular", m_lightOption.specular);

		OBJECTSHADER->SetUniformFloat("spotLight.constant", 1.0f);
		OBJECTSHADER->SetUniformFloat("spotLight.linear", 0.027f);
		OBJECTSHADER->SetUniformFloat("spotLight.quadratic", 0.0028f);
	}
}

void LightObject::Update(float deltaTime) {
	//// 밝기 조절
	if (m_lightOnOff) {
		static float lightChangedAngle = 0.f;
		static float lightDir{ 1.f };

		float maxColorRGB{ std::max({ m_lightColor.x, m_lightColor.y, m_lightColor.z }) };
		float minColorRGB{ std::min({ m_lightColor.x, m_lightColor.y, m_lightColor.z }) };

		m_lightColor += glm::vec3{ std::sinf(glm::radians(lightChangedAngle)) };

		lightChangedAngle += 0.1f * lightDir * deltaTime;

		if (maxColorRGB >= 1.f) {
			m_lightColor -= glm::vec3{ maxColorRGB - 1.f };
			lightDir = -1.f;
		}
		else if (maxColorRGB <= 0.f) {
			m_lightColor += glm::vec3{ -maxColorRGB };
			lightDir = 1.f;
		}
	}

	//// 원운동 
	static float angle = 0.f;
	if (m_orbit) {
		m_position.x = m_radius * std::cosf(glm::radians(angle));
		m_position.z = m_radius * std::sinf(glm::radians(angle));
		angle += m_angleSpeed * deltaTime;

		if (angle > 360.f) {
			angle = 0.f;
		}

	}
	m_lightOption.position = m_position;
}

void LightObject::Render() {
	glm::mat4 unit{ 1.f };
	glm::vec3 ypr{ glm::radians(m_rotateAngle) };

	glm::mat4 scaleMat = glm::scale(unit, m_scaleFactor);
	glm::mat4 rotateMat = glm::yawPitchRoll(ypr.y, ypr.x, ypr.z);
	glm::mat4 translateMat = glm::translate(unit, m_position);

	m_transform = translateMat * rotateMat * scaleMat;

	LIGHTOBJECTSHADER->SetUniformVec3("objectColor", m_lightColor);
	LIGHTOBJECTSHADER->SetUniformMat4("initTransform", m_initTransform);
	LIGHTOBJECTSHADER->SetUniformMat4("modelTransform", m_transform);
	LIGHTOBJECTSHADER->SetUniformMat4("parentTransform", m_parentTransform);

	LIGHTOBJECTSHADER->UseProgram();

	m_model->SetDrawMode(GL_TRIANGLES);

	m_model->Render();

	LIGHTOBJECTSHADER->UnUseProgram();
}
