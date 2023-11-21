#pragma once
#include "Object/Object.h"

struct LightOption {
	glm::vec3 position{ };
	glm::vec3 ambient{ 0.5f }; // 주변광 정도
	glm::vec3 diffuse{ 0.5f }; // 난반사 정도
	glm::vec3 specular{ 1.f }; // 정반사 정도
};

class LightObject : public Object {
public:
	LightObject();
	LightObject(const std::string& modelTag);
	LightObject(const std::string& modelTag, const glm::vec3& lightColor);
	LightObject(const std::string& modelTag, const glm::vec3& lightCOlor, const glm::vec3& objectPosition);
	~LightObject();

private:
	glm::vec3 m_lightColor{ 1.f };
	LightOption m_lightOption{ };

	bool m_directionLightingOn{ false };
	bool m_sportLightingOn{ false };

public:
	void SetLightOption();

	glm::vec3 GetLightColor() const { return m_lightColor; }

public:
	void Update(float deltaTime);
	void Render() override;
};