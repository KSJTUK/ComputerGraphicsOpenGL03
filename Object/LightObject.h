#pragma once
#include "Object/Object.h"

class LightObject : public Object {
public:
	LightObject();
	~LightObject();

private:
	glm::vec3 m_lightColor{ 1.f };

public:
	glm::vec3 GetLightColor() const { return m_lightColor; }

public:
	void Update(float deltaTime);
	void Render();

};