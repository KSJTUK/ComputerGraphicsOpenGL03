#include "pch.h"
#include "WorldScene.h"
#include "ParticleSystem.h"
#include "Object/Cube.h"
#include "Object/LightObject.h"
#include "Graphics/Shader.h"
#include "SkyBox.h"
#include "Terrain.h"

WorldScene1::WorldScene1() { }

WorldScene1::~WorldScene1() { }

void WorldScene1::Init() {
	BACKGROUNDSHADER->UseProgram();
	m_background = std::make_unique<SkyBox>();
	BACKGROUNDSHADER->UnUseProgram();

	OBJECTSHADER->UseProgram();
	m_cone = std::make_unique<Cube>("cone");
	m_cone->SetObjectColor(glm::vec3{ 0.f, 1.f, 1.f });
	m_cone->SEtScale(glm::vec3{ 3.f });

	m_sphere.push_back(std::make_unique<Cube>("sphere"));
	m_sphere.back()->SEtScale(glm::vec3{ 0.3f });
	m_sphere.back()->SetPosition(glm::vec3{ 6.f, 0.f, 0.f });
	m_sphere.back()->SetObjectColor(glm::vec3{1.f, 0.f, 0.f});

	m_sphere.push_back(std::make_unique<Cube>("sphere"));
	m_sphere.back()->SEtScale(glm::vec3{ 0.3f });
	m_sphere.back()->SetOrbitAxis(glm::normalize(glm::vec3{ -1.f, 1.f, -1.f }));
	m_sphere.back()->SetPosition(glm::vec3{ 4.f, 4.f, 4.f });
	m_sphere.back()->SetObjectColor(glm::vec3{ 0.f, 1.f, 0.f });


	m_sphere.push_back(std::make_unique<Cube>("sphere"));
	m_sphere.back()->SEtScale(glm::vec3{ 0.3f });
	m_sphere.back()->SetPosition(glm::vec3{ 0.f, 6.f, 0.f });
	m_sphere.back()->SetOrbitAxis(glm::vec3{ 1.f, 0.f, 0.f });
	m_sphere.back()->SetObjectColor(glm::vec3{ 0.f, 0.f, 1.f });

	OBJECTSHADER->UnUseProgram();

	for (auto& s : m_sphere) {
		s->StartOrbit();
	}

	LIGHTOBJECTSHADER->UseProgram();
	m_lightObject = std::make_unique<LightObject>("sphere", glm::vec3{ 1.f });
	m_lightObject->SEtScale(glm::vec3{ 0.1f });
	m_lightObject->SetPosition(glm::vec3{ 10.f, 2.f, 0.f });
	LIGHTOBJECTSHADER->UnUseProgram();

	TERRAINSHADER->UseProgram();
	m_ground = std::make_unique<Terrain>(glm::uvec2{ 20, 20 });
	TERRAINSHADER->UnUseProgram();

	PARTICLESHADER->UseProgram();
	auto particleGenerateArea = std::make_pair(glm::vec3{ -100.f, 100.f, -100.f }, glm::vec3{ 100.f, 100.f, 100.f });
	m_particleSystem.push_back(std::make_unique<ParticleSystem>(particleGenerateArea, 30.f, 500, 0.3f));
	PARTICLESHADER->UnUseProgram();
}

void WorldScene1::Input(unsigned char key, bool down) {
	if (!down) {
		return;
	}

	if (key == '[') {
		OBJECTSHADER->UseProgram();
		m_cone->CreateSierpinskiTriangle(2);
		m_cone->SetObjectColor(glm::vec3{ 0.f, 1.f, 1.f });
		OBJECTSHADER->UnUseProgram();
	}

	if (key == 'o') {
		for (auto& ps : m_particleSystem) {
			ps->IncGenerateTime();
		}
	}

	if (key == 'p') {
		for (auto& ps : m_particleSystem) {
			ps->DecGenerateTime();
		}
	}

	if (key == 'r') {
		for (auto& sphere : m_sphere) {
			sphere->StartOrbit();
		}
	}

	if (key == 'u') {
		m_lightObject->StartOnOff();
	}

	if (key == 'i') {
		m_lightObject->StopOnOff();
	}

	if (key == 't') {
		m_lightObject->SetLightColor(glm::linearRand(glm::vec3{ }, glm::vec3{ 1.f }));
	}

	if (key == '/') {
		m_lightObject->StartOrbit();
	}

	if (key == ',') {
		m_lightObject->IncOrbitRadius();
	}

	if (key == '.') {
		m_lightObject->DecOrbitRadius();
	}

	if (key == ';') {
		m_lightObject->IncAngleSpeed();
	}

	if (key == '\'') {
		m_lightObject->DecAngleSpeed();
	}
}

void WorldScene1::Update(float deltaTime) {
	PARTICLESHADER->UseProgram();
	for (auto& ps : m_particleSystem) {
		ps->Update(deltaTime);
	}
	PARTICLESHADER->UnUseProgram();

	for (auto& s : m_sphere) {
		s->Update(deltaTime);
	}

	m_lightObject->Update(deltaTime);
	m_cone->Update(deltaTime);
}

void WorldScene1::Render() {
	BACKGROUNDSHADER->UseProgram();
	m_background->Render();
	BACKGROUNDSHADER->UnUseProgram();

	TERRAINSHADER->UseProgram();
	m_ground->Render();
	TERRAINSHADER->UnUseProgram();

	for (auto& ps : m_particleSystem) {
		ps->Render();
	}

	OBJECTSHADER->UseProgram();

	m_lightObject->SetLightOption();

	for (auto& s : m_sphere) {
		s->Render();
	}

	OBJECTSHADER->UnUseProgram();
	
	LIGHTOBJECTSHADER->UseProgram();
	m_lightObject->Render();
	LIGHTOBJECTSHADER->UnUseProgram();
}