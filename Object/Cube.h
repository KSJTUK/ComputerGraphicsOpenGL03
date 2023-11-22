#pragma once
#include "Object/Object.h"

class Cube : public Object {
public:
	Cube();
	~Cube();

	Cube(const std::string& modelTag);
	Cube(const glm::mat4& initTransform);
	Cube(const glm::vec3& initPosition, const glm::vec3& initRotate, const glm::vec3& initScale);

private:
	float radius{ 900.f };
	float angleSpeed{ 10.f };

	bool m_orbit{ false };
	bool m_rotate{ false };

public:
	void StartOrbit() { m_orbit = true; }
	void StopOrbit() { m_orbit = false; }

	void StartRotate() { m_rotate = true; }
	void StopRotate() { m_rotate = false; }

	void Update(float deltaTime) override;
	void Render();
};