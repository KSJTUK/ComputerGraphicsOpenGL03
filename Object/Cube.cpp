#include "pch.h"
#include "Cube.h"
#include "Graphics/Shader.h"
#include "Model/Model.h"
#include "Model/ModelList.h"

Cube::Cube() : Object{ "earth" } {
	m_objectColor = glm::vec3{ 1.f, 0.3f, 0.31f };
	m_scaleFactor = glm::vec3{ 0.3f, 0.3f, 0.3f };
}

Cube::~Cube() { }

void Cube::Update(float deltaTime) {
	static float angle = 0.f;

	m_position.x += radius * std::cosf(glm::radians(angle));
	m_position.z += radius * std::sinf(glm::radians(angle));
	angle += angleSpeed * deltaTime;

	if (angle > 360.f) {
		angle = 0.f;
	}
}

void Cube::Render() {
	Object::Render();
}
