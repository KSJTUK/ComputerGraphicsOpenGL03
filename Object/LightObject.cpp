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

LightObject::LightObject(const std::string& modelTag, const glm::vec3& lightColor, const glm::vec3& objectPosition) : Object { modelTag, lightColor }, m_lightColor{ lightColor } {
	m_position = objectPosition;
}

LightObject::~LightObject() { }

void LightObject::StartOnOff() {
	m_lightOnOff = true;
}

void LightObject::StopOnOff() {
	m_lightOnOff = false;
}

void LightObject::SetLightOption() {
	glm::vec3 ambientColor{ m_lightColor * m_lightOption.ambient };
	glm::vec3 diffuseColor{ m_lightColor * m_lightOption.diffuse };
	m_lightOption.specular = m_lightColor;

	// phong, point lighting
	OBJECTSHADER->SetUniformVec3("pointLight.position", m_lightOption.position);

	//// Direction Lighting
	//if (m_directionLightingOn) {
	//	OBJECTSHADER->SetUniformVec3("dirLight.direction", glm::vec3{ -0.2f, -1.f, -0.3f });
	//	OBJECTSHADER->SetUniformVec3("dirLight.ambient", glm::vec3{ 0.05f });
	//	OBJECTSHADER->SetUniformVec3("dirLight.diffuse", glm::vec3{ 0.1f });
	//	OBJECTSHADER->SetUniformVec3("dirLight.specular", glm::vec3{ 0.7f });
	//}

	 //point, flash lightting
	OBJECTSHADER->SetUniformVec3("pointLight.ambient", ambientColor);
	OBJECTSHADER->SetUniformVec3("pointLight.diffuse", diffuseColor);
	OBJECTSHADER->SetUniformVec3("pointLight.specular", m_lightOption.specular);

	OBJECTSHADER->SetUniformFloat("pointLight.constant", 1.0f);
	OBJECTSHADER->SetUniformFloat("pointLight.linear", 0.0014f);
	OBJECTSHADER->SetUniformFloat("pointLight.quadratic", 0.00007f);
}

void LightObject::SetLightOptionInTerrain() {
	glm::vec3 diffuseColor{ m_lightColor * m_lightOption.diffuse };
	glm::vec3 ambientColor{ m_lightColor * m_lightOption.ambient };
	m_lightOption.specular = m_lightColor;

	// phong, point lighting
	TERRAINSHADER->SetUniformVec3("pointLight.position", m_lightOption.position);

	// Direction Lighting
	if (m_directionLightingOn) {
		TERRAINSHADER->SetUniformVec3("dirLight.direction", glm::vec3{ 0.f, -1.f, 0.f });
		TERRAINSHADER->SetUniformVec3("dirLight.ambient", ambientColor);
		TERRAINSHADER->SetUniformVec3("dirLight.diffuse", diffuseColor);
		TERRAINSHADER->SetUniformVec3("dirLight.specular", glm::vec3{ 0.f });
	}

	//point, flash lightting
	TERRAINSHADER->SetUniformVec3("pointLight.ambient", ambientColor);
	TERRAINSHADER->SetUniformVec3("pointLight.diffuse", diffuseColor);
	TERRAINSHADER->SetUniformVec3("pointLight.specular", m_lightOption.specular);

	TERRAINSHADER->SetUniformFloat("pointLight.constant", 1.0f);
	TERRAINSHADER->SetUniformFloat("pointLight.linear", 0.0014f);
	TERRAINSHADER->SetUniformFloat("pointLight.quadratic", 0.00007f);
}

void LightObject::TurnOnOffSpotLight() {
	m_sportLightingOn = !m_sportLightingOn;
	if (m_sportLightingOn) {
		glm::vec3 diffuseColor{ m_lightColor * m_spotLightOption.diffuse };
		glm::vec3 ambientColor{ diffuseColor * m_spotLightOption.ambient };
		m_lightOption.specular = m_lightColor;

		OBJECTSHADER->SetUniformVec3("spotLight.ambient", ambientColor);
		OBJECTSHADER->SetUniformVec3("spotLight.diffuse", diffuseColor);
		OBJECTSHADER->SetUniformVec3("spotLight.specular", m_spotLightOption.specular);

		OBJECTSHADER->SetUniformFloat("spotLight.constant", 1.0f);
		OBJECTSHADER->SetUniformFloat("spotLight.linear", 0.0014f);
		OBJECTSHADER->SetUniformFloat("spotLight.quadratic", 0.00007f);

		TERRAINSHADER->SetUniformVec3("spotLight.ambient", ambientColor);
		TERRAINSHADER->SetUniformVec3("spotLight.diffuse", diffuseColor);
		TERRAINSHADER->SetUniformVec3("spotLight.specular", m_spotLightOption.specular);

		TERRAINSHADER->SetUniformFloat("spotLight.constant", 1.0f);
		TERRAINSHADER->SetUniformFloat("spotLight.linear", 0.0014f);
		TERRAINSHADER->SetUniformFloat("spotLight.quadratic", 0.00007f);
	}
	else {
		OBJECTSHADER->SetUniformVec3("spotLight.ambient", glm::vec3{ 0.f });
		OBJECTSHADER->SetUniformVec3("spotLight.diffuse", glm::vec3{ 0.f });
		OBJECTSHADER->SetUniformVec3("spotLight.specular", glm::vec3{ 0.f });

		OBJECTSHADER->SetUniformFloat("spotLight.constant", 0.f);
		OBJECTSHADER->SetUniformFloat("spotLight.linear", 0.f);
		OBJECTSHADER->SetUniformFloat("spotLight.quadratic", 0.f);

		TERRAINSHADER->SetUniformVec3("spotLight.ambient", glm::vec3{ 0.f });
		TERRAINSHADER->SetUniformVec3("spotLight.diffuse", glm::vec3{ 0.f });
		TERRAINSHADER->SetUniformVec3("spotLight.specular", glm::vec3{ 0.f });

		TERRAINSHADER->SetUniformFloat("spotLight.constant", 0.f);
		TERRAINSHADER->SetUniformFloat("spotLight.linear", 0.f);
		TERRAINSHADER->SetUniformFloat("spotLight.quadratic", 0.f);
	}
}

void LightObject::SetTransform() {
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
	SetTransform();

	LIGHTOBJECTSHADER->UseProgram();

	m_model->SetDrawMode(GL_TRIANGLES);

	m_model->Render();

	LIGHTOBJECTSHADER->UnUseProgram();
}
