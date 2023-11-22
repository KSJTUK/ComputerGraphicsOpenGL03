#pragma once

class Tank {
public:
	Tank();
	Tank(const glm::vec3& initPosition);
	~Tank();

private:
	std::vector<class Object*> m_tankParts{ };
	enum {
		MAIN_PART = 0,
		LOOP_TOP,
		LEFT_MISSILE,
		RIGHT_MISSILE,
		LEFT_HORN,
		RIGHT_HORN,
		MAIN_MISSILE
	};

	float m_deltaTime{ };
	glm::vec3 m_position{ };
	glm::vec3 m_prevPosition{ };
	glm::vec3 m_direction{ 0.f, 0.f, 1.f };
	float m_speed{ 200.f };

	bool m_autoMoveMode{ false };
	bool m_missileAutoMove{ false };
	bool m_missileAutoRotate{ false };
	bool m_hornAutoMove{ false };

	float m_missileMinRotate{ 10.f };
	float m_missileMaxRotate{ 60.f };

	int m_rotateTop{ 0 };
	float m_rotateTopDir{ 0.f };

private:
	bool m_missileAngleIndex{ 0 };
	const glm::vec3 m_leftMissileAngles[2]{ { 90.f, 10.f, 0.f }, { 90.f, -60.f, 0.f } };
	const glm::vec3 m_rightMissileAngles[2]{ { 90.f, -10.f, 0.f }, { 90.f, 60.f, 0.f } };

	bool m_hornMoveAngleIndex{ 0 };
	const glm::vec3 m_leftHornAngles[2]{ { 45.f, 0.f, 0.f }, { -45.f, 0.f, 0.f } };
	const glm::vec3 m_rightHornAngles[2]{ { -45.f, 0.f, 0.f }, { 45.f, 0.f, 0.f } };

	bool m_missileAutoMoveIndex{ };
	glm::vec3 m_leftMissileMovePoints[2]{ { }, { } };
	glm::vec3 m_rightMissileMovePoints[2]{ { }, { } };

	void AutoMoveHorn();
	void AutoMoveMissile();
	void AutoRotateMissile();
	void Fire();

public:
	void Input(unsigned char key, bool down);
	void SpecialInput(int key, bool down);
	void Move(const glm::vec3& moveDirection);
	void AutoMove(const glm::vec3& moveDirection);

public:
	void Update(float deltaTime);

	void Render();
};

