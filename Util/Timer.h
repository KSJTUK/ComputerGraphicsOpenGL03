#pragma once

// Ÿ�̸� ����� �� Ŭ����
class Timer {
public:
	Timer();
	~Timer();

private:
	// ������ �̿��Ͽ� �ð��� ���
	uint64 m_tick{ };
	uint64 m_prev{ };

	// �ð� ��� ���� ����
	float m_timeScale{ 1.f };
	// ��Ÿ Ÿ��
	float m_deltaTime{ };
	// ���ۺ��� �帥 �ð��� ������ ����
	float m_timeElapsed{ 0.0f };
	// ������ ���� ����
	int m_frameCount{ };
	float m_fps{ };

public:
	//Setter and Getter
	void SetTimeScale(float timeScale);
	float GetDeltaTime() const;
	float GetTimeScale() const;
	float GetFrame() const;

public:
	void Init();
	void Update();
};

