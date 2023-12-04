#pragma once
#include "Object/Object.h"

class Cube : public Object {
public:
	Cube();
	~Cube();

	Cube(const std::string& modelTag);
	Cube(const std::string& modelTag, const glm::mat4& initTransform);
	Cube(const glm::vec3& initPosition, const glm::vec3& initRotate, const glm::vec3& initScale);

private:
	float radius{ 900.f };
	float angleSpeed{ 10.f };

	bool m_orbit{ false };
	bool m_rotate{ false };

	glm::vec3 m_orbitAxis{ 0.f, 1.f, 0.f };

public:
	void SetOrbitAxis(const glm::vec3& axis);

	void Orbit();

	void StartOrbit() { m_orbit = true; }
	void StopOrbit() { m_orbit = false; }

	void StartRotate() { m_rotate = true; }
	void StopRotate() { m_rotate = false; }

	void SetTransform();
	void BindingTexture();

	void Update(float deltaTime) override;
	void Render();
};