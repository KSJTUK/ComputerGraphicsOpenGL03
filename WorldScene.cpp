#include "pch.h"
#include "WorldScene.h"
#include "Object/Cube.h"
#include "Object/LightObject.h"
#include "Graphics/Shader.h"

void WorldScene1::Init() {
	SHADER->UseProgram();
	m_earth = std::make_unique<Cube>("earth");
	m_earth->SEtScale(glm::vec3{ 0.01f });
	m_earth->SetPosition(glm::vec3{ 0.f });

	SHADER->UnUseProgram();

	LIGHTOBJECTSHADER->UseProgram();
	m_lightObject = std::make_unique<LightObject>("sphere", glm::vec3{ 1.f });
	m_lightObject->SEtScale(glm::vec3{ 0.1f });
	m_lightObject->SetPosition(glm::vec3{ 3.f, 0.f, 0.f });
	LIGHTOBJECTSHADER->UnUseProgram();
}

void WorldScene1::Input(unsigned char key, bool down) {
	if (!down) {
		return;
	}

	if (key == 'r') {
		m_earth->StartRotate();
	}

	if (key == '[') {
		m_earth->StopRotate();
	}
	if (key == ']') {
		m_lightObject->StopOrbit();
	}

	if (key == 'y') {
		m_lightObject->StartOrbit();
	}

	if (key == 'o') {
		m_lightObject->IncOrbitRadius();
	}
	if (key == 'p') {
		m_lightObject->DecOrbitRadius();
	}

	if (key == 'z') {
		m_lightObject->StartOnOff();
	}

	if (key == 'x') {
		m_lightObject->StopOnOff();
	}

	if (key == 'c') {
		m_lightObject->IncAngleSpeed();
	}

	if (key == 'v') {
		m_lightObject->DecAngleSpeed();
	}

	if (key == 'i') {
		m_lightObject->SetLightColor(glm::linearRand(glm::vec3{ 0.f }, glm::vec3{ 1.f }));
	}

	if (key == 'u') {
		m_lightObject->SetLightColor(glm::vec3{ 1.f });
	}

	if (key == 'k') {
		if (m_earth->GetModelTag() == "earth") {
			m_earth.release();
			m_earth = std::make_unique<Cube>("cube");
			m_earth->SEtScale(glm::vec3{ 1.f });
		}
		else {
			m_earth.release();
			m_earth = std::make_unique<Cube>("earth");
			m_earth->SEtScale(glm::vec3{ 0.01f });
		}
	}
}

void WorldScene1::Update(float deltaTime) {
	m_earth->Update(deltaTime);
	m_lightObject->Update(deltaTime);
}

void WorldScene1::Render() {
	SHADER->UseProgram();
	m_earth->SetMeterials();
	m_lightObject->SetLightOption();
	m_earth->Render();
	SHADER->UnUseProgram();
	
	LIGHTOBJECTSHADER->UseProgram();
	m_lightObject->Render();
	LIGHTOBJECTSHADER->UnUseProgram();
}
