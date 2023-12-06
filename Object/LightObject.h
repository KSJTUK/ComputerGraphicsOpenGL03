#pragma once
#include "Object/Object.h"

struct LightOption {
	glm::vec3 position{ };
	glm::vec3 ambient{ 0.1f }; // 주변광 정도
	glm::vec3 diffuse{ 1.0f }; // 난반사 정도
	glm::vec3 specular{ 1.f }; // 정반사 정도
};

struct SpotLightOption {
	glm::vec3 ambient{ 0.f }; // 주변광 정도
	glm::vec3 diffuse{ 1.0f }; // 난반사 정도
	glm::vec3 specular{ 1.f }; // 정반사 정도
};

class LightObject : public Object {
public:
	LightObject();
	LightObject(const std::string& modelTag);
	LightObject(const std::string& modelTag, const glm::vec4& lightColor);
	LightObject(const std::string& modelTag, const glm::vec4& lightCOlor, const glm::vec3& objectPosition);
	~LightObject();

private:
	glm::vec4 m_lightColor{ 1.f };
	LightOption m_lightOption{ };
	SpotLightOption m_spotLightOption{ };

	bool m_directionLightingOn{ false };
	bool m_sportLightingOn{ false };

	float m_radius{ 3.f };
	float m_angleSpeed{ 1.f };
	bool m_orbit{ false };
	bool m_rotate{ false };

	bool m_lightOnOff{ false };

public:
	void IncOrbitRadius() { m_radius += 1.f; }
	void DecOrbitRadius() { m_radius -= 1.f; }

	void IncAngleSpeed() { m_angleSpeed += 1.f; }
	void DecAngleSpeed() { m_angleSpeed -= 1.f; }
	
	void StartOrbit() { m_orbit = true; }
	void StopOrbit() { m_orbit = false; }
	void StartRotation() { m_rotate = true; }
	void StopRotation() { m_rotate = false; }
	void StartOnOff();
	void StopOnOff();

	void SetLightOption();
	void SetLightOptionInTerrain();

	void TurnOnOffSpotLight();

	void SetTransform();

	void SetLightColor(const glm::vec4& color) { m_lightColor = color; }
	glm::vec4 GetLightColor() const { return m_lightColor; }

public:
	void Update(float deltaTime);
	void Render() override;
};