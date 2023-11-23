#include "pch.h"
#include "WorldScene.h"
#include "ParticleSystem.h"
#include "Object/Cube.h"
#include "Object/LightObject.h"
#include "Graphics/Shader.h"
#include "Terrain.h"

WorldScene1::WorldScene1() { }

WorldScene1::~WorldScene1() { }

void WorldScene1::Init() {
	OBJECTSHADER->UseProgram();
	m_earth = std::make_unique<Cube>("earth");
	m_earth->SEtScale(glm::vec3{ 0.01f });
	m_earth->SetPosition(glm::vec3{ 0.f });
	OBJECTSHADER->UnUseProgram();

	LIGHTOBJECTSHADER->UseProgram();
	m_lightObject = std::make_unique<LightObject>("sphere", glm::vec3{ 1.f });
	m_lightObject->SEtScale(glm::vec3{ 0.1f });
	m_lightObject->SetPosition(glm::vec3{ 3.f, 0.f, 0.f });
	LIGHTOBJECTSHADER->UnUseProgram();

	TERRAINSHADER->UseProgram();
	m_ground = std::make_unique<Terrain>(glm::uvec2{ 20, 20 });
	TERRAINSHADER->UnUseProgram();

	PARTICLESHADER->UseProgram();
	auto particleGenerateArea = std::make_pair(glm::vec3{ -10.f, 20.f, -10.f }, glm::vec3{ 10.f, 20.f, 10.f });
	m_particleSystem = std::make_unique<ParticleSystem>(particleGenerateArea, 20.f, 500, 0.00001f);
	PARTICLESHADER->UnUseProgram();
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
			m_earth->SetObjectColor(glm::linearRand(glm::vec3{ }, glm::vec3{ 1.f }));
		}
		else {
			m_earth.release();
			m_earth = std::make_unique<Cube>("earth");
			m_earth->SEtScale(glm::vec3{ 0.01f });
			m_earth->SetObjectColor(glm::vec3{ 1.f });
		}
	}
}

void WorldScene1::Update(float deltaTime) {
	m_earth->Update(deltaTime);
	m_lightObject->Update(deltaTime);
	m_particleSystem->Update(deltaTime);
}

void WorldScene1::Render() {
	TERRAINSHADER->UseProgram();
	m_ground->Render();
	TERRAINSHADER->UnUseProgram();

	OBJECTSHADER->UseProgram();

	m_earth->SetMeterials();
	for (auto& sphere : m_spheres) {
		sphere->SetMeterials();
	}
	m_earth->Render();

	m_lightObject->SetLightOption();

	//m_earth->Render();
	for (auto& sphere : m_spheres) {
		sphere->Render();
	}


	OBJECTSHADER->UnUseProgram();
	
	LIGHTOBJECTSHADER->UseProgram();
	m_lightObject->Render();
	LIGHTOBJECTSHADER->UnUseProgram();

	m_particleSystem->Render();
}
