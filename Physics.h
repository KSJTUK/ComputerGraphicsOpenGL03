#pragma once

class Physics {
public:
	Physics();
	~Physics();

private:
	float m_deltaTime{ };

public:
	void Move();
	void Jump();
	void SetPower();
	void AddPower();
	void Gravity();

	void Update(float deltaTime);
};