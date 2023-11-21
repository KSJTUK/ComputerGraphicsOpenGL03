#include "pch.h"
#include "Cube.h"
#include "Graphics/Shader.h"
#include "Model/Model.h"
#include "Model/ModelList.h"

Cube::Cube() : Object{ "earth" } {

}

Cube::~Cube() { }

void Cube::Update(float deltaTime) {
	static float angle = 0.f;

	m_position.x = radius * std::cosf(glm::radians(angle));
	m_position.z = radius * std::sinf(glm::radians(angle));
	angle += angleSpeed * deltaTime;

	if (angle > 360.f) {
		angle = 0.f;
	}
}

void Cube::Render() {
	Object::Render();
}
