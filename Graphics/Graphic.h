#pragma once

class GameWorld {
public:
	GameWorld();
	~GameWorld();

private:
	bool m_isInited{ false };
	std::unique_ptr<class Camera> m_camera{ };

private:
	// ī�޶� �ܺ��Ķ���� (��������� ������ �� ���� ������)
	float m_fovy{ 90.f }; // ���� �þ߰�

	// ��ũ�� ȭ���� ũ�⸦ �˾Ƴ��� ���� WindowInfo��ü ����
	std::shared_ptr<struct WindowInfo> m_windowInfo{ }; // aspect(��Ⱦ��) = width / height

	float m_near{ 0.1f };           // �þ� ����ü�� ����� ������ �Ÿ�
	float m_far{ 1000.f };           // �þ� ����ü�� �� ������ �Ÿ�

	glm::mat4 m_perspectiveMatrix{ 1.f };

	float m_deltaTime{ };

	// test--------------------------------------------
	class Cube* m_cube{ };
	std::vector<class Cube*> m_cubes{ };
	class LightObject* m_lightObj{ };

	const int m_objectTesselLevel{ 6 };
	const int m_objectTesselOff{ 1 };
	// ------------------------------------------------

public:
	// getter
	bool IsInited() const;

	// setter
	void SetWindowInfo(std::shared_ptr<struct WindowInfo>& winInfo);
	void CalcPerspectiveMat();

public:
	// �ܺ� Ű�Է��� ī�޶󿡰� �����ִ� �Լ�
	void Input(unsigned char key, bool down);
	void SpecialInput(int key, bool down);
	void MouseMotionInput(int x, int y, int prevX, int prevY);
	void MousePassiveMotionInput(int x, int y, int prevX, int prevY);

public:
	void Init();
	void Update(float deltaTime);
	void Render();
};

