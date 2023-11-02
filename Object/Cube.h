#pragma once
#include "Object/Object.h"

class Cube : public Object {
public:
	Cube();
	~Cube();

	Cube(const glm::mat4& initTransform);
	Cube(const glm::vec3& initPosition, const glm::vec3& initRotate, const glm::vec3& initScale);

private:
	std::string m_modelTag{ "cube" };
	glm::vec3 m_cubeColor{ };

public:
	void Update(float deltaTime) override;
	void Render();
};