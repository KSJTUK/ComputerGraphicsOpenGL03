#include "pch.h"
#include "WorldScene.h"
#include "Graphics/ParticleSystem.h"
#include "Object/Cube.h"
#include "Object/LightObject.h"
#include "Graphics/Shader.h"
#include "Graphics/SkyBox.h"
#include "Graphics/Terrain.h"

WorldScene1::WorldScene1() { }

WorldScene1::~WorldScene1() { }

void WorldScene1::Init() {
	m_sphere.push_back(std::make_unique<Cube>("sphere"));
	m_sphere.back()->SetScale(glm::vec3{ 0.3f });
	m_sphere.back()->SetPosition(glm::vec3{ 6.f, 0.f, 0.f });
	m_sphere.back()->SetObjectColor(glm::vec3{1.f, 0.f, 0.f});

	m_sphere.push_back(std::make_unique<Cube>("sphere"));
	m_sphere.back()->SetScale(glm::vec3{ 0.3f });
	m_sphere.back()->SetOrbitAxis(glm::normalize(glm::vec3{ -1.f, 1.f, -1.f }));
	m_sphere.back()->SetPosition(glm::vec3{ 4.f, 4.f, 4.f });
	m_sphere.back()->SetObjectColor(glm::vec3{ 0.f, 1.f, 0.f });


	m_sphere.push_back(std::make_unique<Cube>("sphere"));
	m_sphere.back()->SetScale(glm::vec3{ 0.3f });
	m_sphere.back()->SetPosition(glm::vec3{ 0.f, 6.f, 0.f });
	m_sphere.back()->SetOrbitAxis(glm::vec3{ 1.f, 0.f, 0.f });
	m_sphere.back()->SetObjectColor(glm::vec3{ 0.f, 0.f, 1.f });

	for (auto& s : m_sphere) {
		s->StartOrbit();
	}

	auto particleGenerateArea = std::make_pair(glm::vec3{ -100.f, 100.f, -100.f }, glm::vec3{ 100.f, 100.f, 100.f });
	m_particleSystem.push_back(std::make_unique<ParticleSystem>(particleGenerateArea, 30.f, 500, 0.3f));
}

void WorldScene1::Input(unsigned char key, bool down) {
	if (!down) {
		return;
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
}

void WorldScene1::Update(float deltaTime) {
	for (auto& ps : m_particleSystem) {
		ps->Update(deltaTime);
	}

	for (auto& s : m_sphere) {
		s->Update(deltaTime);
	}
}

void WorldScene1::Render() {
	for (auto& ps : m_particleSystem) {
		ps->Render();
	}

	for (auto& s : m_sphere) {
		s->Render();
	}
}