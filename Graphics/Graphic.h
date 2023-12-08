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
	float m_fovy{ 120.f }; // ���� �þ߰�

	// ��ũ�� ȭ���� ũ�⸦ �˾Ƴ��� ���� WindowInfo��ü ����
	std::shared_ptr<struct WindowInfo> m_windowInfo{ }; // aspect(��Ⱦ��) = width / height

	float m_near{ 0.1f };           // �þ� ����ü�� ����� ������ �Ÿ�
	float m_far{ 1000.f };           // �þ� ����ü�� �� ������ �Ÿ�

	glm::mat4 m_perspectiveMatrix{ 1.f };

	float m_deltaTime{ };

	// test--------------------------------------------
	std::unique_ptr<class LightObject> m_light{ };

	std::unique_ptr<class SkyBox> m_background{ };
	std::unique_ptr<class Terrain> m_ground{ };

	std::unique_ptr<class Reticle> m_testReticle{ };
	std::unique_ptr<class UI> m_testUI{ };

	std::unordered_map<std::string, std::pair<std::list<class Object*>, std::list<class Object*>>> m_collisionPairs{};
	std::list<class Object*> m_objects{ };

	std::vector<class WorldScene*> m_scenes{ };
	int m_sceneIndex{ };

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

	void AddCollisionPair(const std::string& groub, Object* obj1, Object* obj2);
	void Collision();

	void SetPerspectiveAllShader();
	void SetViewMatAllShader(const glm::mat4& viewMat);

	void WorldRendering();

public:
	void Init();
	void Update(float deltaTime);
	void Render();
//
//public:
//	template <class ObjType>
//	bool TerrainCollision(ObjType& obj) {
//		glm::vec3 objPosition = obj.GetPosition();
//		float groundHeight = m_ground->GetHeight(objPosition);
//		if (groundHeight < -_FMAX + 1.f) {
//			return false;
//		}
//
//		if (objPosition.y > groundHeight) {
//			return false;
//		}
//
//		return true;
//	}
//
//	template <class ObjType>
//	void HandleTerrainCollision(ObjType& obj) {
//		if (TerrainCollision(obj)) {
//			obj.HandleTerrainCollision();
//		}
//	}
};

