#pragma once

class GameWorld {
public:
	GameWorld();
	~GameWorld();

private:
	bool m_isInited{ false };
	std::unique_ptr<class Camera> m_camera{ };

private:
	// 카메라 외부파라미터 (투영행렬을 생성할 떄 쓰일 변수들)
	float m_fovy{ 120.f }; // 수직 시야각

	// 스크린 화면의 크기를 알아내기 위한 WindowInfo객체 참조
	std::shared_ptr<struct WindowInfo> m_windowInfo{ }; // aspect(종횡비) = width / height

	float m_near{ 0.1f };           // 시야 절두체의 가까운 평면과의 거리
	float m_far{ 1000.f };           // 시야 절두체의 먼 평면과의 거리

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
	// 외부 키입력을 카메라에게 전해주는 함수
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

