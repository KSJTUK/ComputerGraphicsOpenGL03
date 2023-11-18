#pragma once

class Engine {
public:
	// �⺻ ����, �Ҹ���
	Engine();
	~Engine();

	// ��ü�� ���縦 ����
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

private:
	std::shared_ptr<WindowInfo> m_windowInfo{ };

	std::unique_ptr<class Timer> m_timer{ nullptr };
	std::unique_ptr<class GameWorld> m_grapics{ nullptr };

	int32 m_mousePrevPos[2]{ };

	float m_deltaTime{ };

private:
	// ����Լ� �������� ���� �Լ��� ����
	void SubscribeCallbacks();

public:
	size_t GetWindowWidth() const;
	size_t GetWindowHeight() const;
	float GetWindowWidthF() const;
	float GetWindowHeightF() const;

	float GetDeltaTime() const { return m_deltaTime; };

	void SetWindowSize(int32 windowWidth, int32 windowHeight);

public:
	// �⺻ ��� ��ü�� ����, ������ ����, �ݹ��Լ� �������� �ϴ� �Լ�
	void Init(int32*, char**);

	// reshape�ݹ� �Լ��� �ҷ��ö� ������ ũ�⸦ ������ �Լ�
	void ReSizeWindow(int32, int32);

	// ���� ���� ������Ʈ �Լ�
	void Update();

	// ������ ��� �Լ�
	void Render();

	// Ű �Է��� ���������� ó���� �Լ�
	void Input(unsigned char key, bool down);
	void SpecialInput(int32 key, bool down);
	void MouseMotionInput(int32 x, int32 y);
	void MousePassiveMotionInpit(int32 x, int32 y);

	// ���� �����Լ�
	void Loop();
	// ���� �����Լ�
	void LoopEnd();



public:

	// ---------------------------------------------------------------
		// �ǽ� Solution�� �ݹ��Լ� ���



public:
	void SubscribeDrawFunc(void(*func)(void));
	void SubscribeIdleFUnc(void(*func)(void));
	void SubscribeReshapeFunc(void(*func)(int, int));
	void SubscribeMouseFunc(void(*func)(int, int, int, int));
	void SubscribeMouseMotionFunc(void(*func)(int, int));
	void SubscribePassiveMotionFunc(void(*func)(int, int));
	void SubscribeKeyboardFunc(void(*func)(unsigned char, int, int));
	void SubscribeKeyboardUpfunc(void(*func)(unsigned char, int, int));
};