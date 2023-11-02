#pragma once
#include "Object/Object.h"

class Cube : public Object {
public:
	Cube();
	~Cube();

private:
	glm::vec3 m_cubeColor{ };

public:
	void Update(float deltaTime) override;
	void Render();
};