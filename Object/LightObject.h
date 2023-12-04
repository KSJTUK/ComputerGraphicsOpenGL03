#pragma once
#include "Object/Object.h"

struct LightOption {
	glm::vec3 position{ };
	glm::vec3 ambient{ 0.5f }; // �ֺ��� ����
	glm::vec3 diffuse{ 0.5f }; // ���ݻ� ����
	glm::vec3 specular{ 1.f }; // ���ݻ� ����
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

	bool m_directionLightingOn{ true };
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

	void SetLightColor(const glm::vec3& color) { m_lightColor = color; }
	glm::vec3 GetLightColor() const { return m_lightColor; }

public:
	void Update(float deltaTime);
	void Render() override;
};