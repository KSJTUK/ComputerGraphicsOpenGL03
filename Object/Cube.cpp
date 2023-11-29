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

void Cube::SetOrbitAxis(const glm::vec3& axis) {
	m_orbitAxis = axis;
}

void Cube::Orbit() {
	m_position = glm::rotate(m_position, glm::radians(0.01f), m_orbitAxis);
}

void Cube::Update(float deltaTime) {
	static float angle = 0.f;
	static float rotateAngle = 0.f;

	if (m_orbit) {
		Orbit();
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