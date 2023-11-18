#pragma once
#include "Object/Object.h"

class Cube : public Object {
public:
	Cube();
	~Cube();

	Cube(const glm::mat4& initTransform);
	Cube(const glm::vec3& initPosition, const glm::vec3& initRotate, const glm::vec3& initScale);

private:
	float radius{ 0.f };
	float angleSpeed{ 10.f };

public:
	void Update(float deltaTime) override;
	void Render();
};