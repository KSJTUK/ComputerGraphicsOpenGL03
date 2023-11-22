#include "pch.h"
#include "Cube.h"
#include "Graphics/Shader.h"
#include "Model/Model.h"
#include "Model/ModelList.h"

Cube::Cube() : Object{ "earth" } {

}

Cube::Cube(const std::string& modelTag) : Object{ modelTag } {

}

Cube::Cube(const std::string& modelTag, const glm::mat4& initTransform) : Object{ modelTag } {
	m_initTransform = initTransform;
}

Cube::~Cube() { }

void Cube::Update(float deltaTime) {
	static float angle = 0.f;
	static float rotateAngle = 0.f;

	if (m_orbit) {
		m_position.x = radius * std::cosf(glm::radians(angle));
		m_position.z = radius * std::sinf(glm::radians(angle));
		angle += angleSpeed * deltaTime;

		if (angle > 360.f) {
			angle = 0.f;
		}
	}

	if (m_rotate) {
		m_rotateAngle.y += angleSpeed * deltaTime;
		if (m_rotateAngle.y > 360.f) {
			m_rotateAngle.y = 0.f;
		}
	}
}

void Cube::Render() {
	Object::Render();
}