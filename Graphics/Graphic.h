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
	float m_far{ 10000.f };           // �þ� ����ü�� �� ������ �Ÿ�

	glm::mat4 m_perspectiveMatrix{ 1.f };

	float m_deltaTime{ };

	// test--------------------------------------------
	std::unique_ptr<class SkyBox> m_background{ };
	std::unique_ptr<class Terrain> m_ground{ };

	std::unique_ptr<class LightObject> m_light{ };
	std::unique_ptr<class ParticleSystem> m_particleSystem{ };

	std::unique_ptr<class TexturedCube> m_textureCube{ };

	std::unordered_map<std::string, std::pair<class Object*, class Object*>> m_collisionPairs{ };
	std::list<class Object*> m_objects{ };

	std::vector<std::unique_ptr<class Cube>> m_belendedCubes{ };

	bool m_cameraMoveOnTerrain{ true };
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

	void SetGLOptions();
	void InitModelList();
	void CreateShaderPrograms();

	void CreateDefaultObjects();

	void SetPerspectiveAllShader();
	void SetViewMatAllShader(const glm::mat4& viewMat);

	void WorldRendering();

public:
	void Init();
	void Update(float deltaTime);
	void Render();
};

