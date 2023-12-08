#include "pch.h"
#include "Graphics/Graphic.h"
#include "Graphics/Shader.h"
#include "Graphics/Camera.h"
#include "Model/ModelList.h"

// test--------------------------------------------
#include "Object/Cube.h"
#include "Object/LightObject.h"
#include "Util/TextureComponent.h"
#include "WorldScene.h"
#include "Terrain.h"
#include "SkyBox.h"
#include "Object/LightObject.h"
#include "Util/UI.h"
// ------------------------------------------------

GameWorld::GameWorld() { }

GameWorld::~GameWorld() { }

bool GameWorld::IsInited() const {
	return m_isInited;
}

void GameWorld::SetWindowInfo(std::shared_ptr<struct WindowInfo>& winInfo) {
	m_windowInfo = winInfo;

	if (m_testReticle) {
		m_testReticle->ResizedWindow();
		m_testUI->ResizedWindow();
	}
	CalcPerspectiveMat();
}

void GameWorld::CalcPerspectiveMat() {
	if (!m_isInited) {
		return;
	}

	float aspect = m_windowInfo->fWidth / m_windowInfo->fHeight;
	float halfFovy = m_fovy / 2.f;

	m_perspectiveMatrix = glm::perspective(glm::radians(halfFovy), aspect, m_near, m_far);
	SetPerspectiveAllShader();
}

void GameWorld::Input(unsigned char key, bool down) {
	m_camera->Input(key, down);
	m_scenes[m_sceneIndex]->Input(key, down);
}

void GameWorld::SpecialInput(int key, bool down) {
	if (down) {
		if (key == GLUT_KEY_F1) {
			m_cameraMoveOnTerrain = !m_cameraMoveOnTerrain;
		}

		if (key == GLUT_KEY_F2) {
			m_camera->TurnOnOffSpotLight();
			m_light->TurnOnOffSpotLight();
		}

		if (key == GLUT_KEY_F3) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		if (key == GLUT_KEY_F4) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
	}
}

void GameWorld::MouseMotionInput(int x, int y, int prevX, int prevY) {
	m_camera->MouseMotionInput(x, y, prevX, prevY);
}

void GameWorld::MousePassiveMotionInput(int x, int y, int prevX, int prevY) {
}

void GameWorld::SetGLOptions() {
	glPointSize(2.f);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void GameWorld::InitModelList() {
	// 모델리스트를 생성하고 모델 불러오기
	OBJECTSHADER->UseProgram();

	MODELLIST->Init();
	MODELLIST->LoadModel("cube.obj");
	MODELLIST->LoadModel("cone.obj");
	MODELLIST->LoadModel("sphere.obj");
	MODELLIST->LoadModel("cylinder.obj");
	MODELLIST->LoadModel("earth.obj", "Earth_diffuse_512p.png");

	OBJECTSHADER->UnUseProgram();
}

void GameWorld::CreateShaderPrograms() {
	// 쉐이더 프로그램 생성
	OBJECTSHADER->CreateShaderProgram();
	LIGHTOBJECTSHADER->CreateShaderProgram();
	PARTICLESHADER->CreateShaderProgram();
	TERRAINSHADER->CreateShaderProgram();
	BACKGROUNDSHADER->CreateShaderProgram();
	UISHADER->CreateShaderProgram();
}

void GameWorld::CreateDefaultObjects() {
	m_light = std::make_unique<LightObject>("sphere", glm::vec3{ 1.f }, glm::vec3{ 0.f, 3.f, 0.f });
	m_light->SetScale(glm::vec3{ 0.2f });

	// 카메라 생성
	m_camera = std::make_unique<Camera>();
	m_camera->Init();

	m_background = std::make_unique<SkyBox>();
	m_ground = std::make_unique<Terrain>(glm::uvec2{ 20, 20 });

	m_testReticle = std::make_unique<Reticle>();
	m_testUI = std::make_unique<UI>();
	m_testUI->SetScreenPosition(glm::vec3{ 100.f, 100.f, 0.f });
}

void GameWorld::AddCollisionPair(const std::string& groub, Object* obj1, Object* obj2) {
	auto iter = m_collisionPairs.find(groub);
	if (iter == m_collisionPairs.end()) {
		m_collisionPairs.insert(std::make_pair(groub, std::pair<std::list<Object*>, std::list<Object*>>{ }));
		iter = m_collisionPairs.find(groub);
	}

	auto listPair = iter->second;
	if (obj1) {
		std::list<Object*>::const_iterator listIter = listPair.first.begin();
		std::list<Object*>::const_iterator listEnd = listPair.first.end();
		bool exist{ false };
		for (; listIter != listEnd; ++listIter) {
			if ((*listIter) == obj1) {
				exist = true;
				return;
			}
		}
		
		if (!exist) {
			listPair.first.push_back(obj1);
		}
	}

	if (obj2) {
		std::list<Object*>::const_iterator listIter = listPair.second.begin();
		std::list<Object*>::const_iterator listEnd = listPair.second.end();
		bool exist{ false };
		for (; listIter != listEnd; ++listIter) {
			if ((*listIter) == obj2) {
				exist = true;
				return;
			}
		}

		if (!exist) {
			listPair.second.push_back(obj2);
		}
	}
}

void GameWorld::Collision() {
	for (auto& iter : m_collisionPairs) {
		const std::string& groub = iter.first;
		auto& list1 = iter.second.first;
		auto& list2 = iter.second.second;

		auto iter1 = list1.begin();
		auto listEnd1 = list1.end();
		for (; iter1 != listEnd1; ++iter1) {
			auto iter2 = list2.begin();
			auto listEnd2 = list2.end();

			for (; iter2 != list2.end(); ++iter2) {
				/*if (IsCollision((*iter1), (*iter2))) {
					(*iter1)->HandleCollision(groub, (*iter2));
					(*iter2)->HandleCollision(groub, (*iter1));
				}*/
			}
		}
	}
}

void GameWorld::SetPerspectiveAllShader() {
	BACKGROUNDSHADER->SetUniformMat4("perspectiveMat", m_perspectiveMatrix);
	TERRAINSHADER->SetUniformMat4("perspectiveMat", m_perspectiveMatrix);
	PARTICLESHADER->SetUniformMat4("perspectiveMat", m_perspectiveMatrix);
	OBJECTSHADER->SetUniformMat4("perspectiveMat", m_perspectiveMatrix);
	LIGHTOBJECTSHADER->SetUniformMat4("perspective", m_perspectiveMatrix);
	UISHADER->SetUniformMat4("perspective", m_perspectiveMatrix);
}

void GameWorld::SetViewMatAllShader(const glm::mat4& viewMat) {
	BACKGROUNDSHADER->SetUniformMat4("viewMat", glm::mat4(glm::mat3(viewMat)));
	UISHADER->SetUniformMat4("view", glm::mat4(glm::mat3(viewMat)));
	TERRAINSHADER->SetUniformMat4("viewMat", viewMat);
	PARTICLESHADER->SetUniformMat4("viewMat", viewMat);
	OBJECTSHADER->SetUniformMat4("viewMat", viewMat);
	LIGHTOBJECTSHADER->SetUniformMat4("view", viewMat);
}

void GameWorld::WorldRendering() {
	m_camera->Render();
	SetViewMatAllShader(m_camera->GetViewMat());


	m_light->SetLightOption();
	m_light->SetLightOptionInTerrain();
	m_light->Render();

	m_background->Render();
	m_ground->Render();
	m_scenes[m_sceneIndex]->Render();

	m_testReticle->Render();
	m_testUI->Render();

	glViewport(0, 0, m_windowInfo->width, m_windowInfo->height);
}

void GameWorld::Init() {
	SetGLOptions();

	CreateShaderPrograms();

	InitModelList();

	CreateDefaultObjects();

	// test--------------------------------------------
	m_scenes.push_back(new WorldScene1{ });
	// ------------------------------------------------

	for (auto& scene : m_scenes) {
		scene->Init();
	}


	// 투영 변환 행렬 계산 및 전송
	CalcPerspectiveMat();

	m_isInited = true;
}

void GameWorld::Update(float deltaTime) {
	m_deltaTime = deltaTime;
	m_light->Update(deltaTime);

	m_camera->Update(m_deltaTime);

	if (m_cameraMoveOnTerrain) {
		glm::vec3 heightPosition = m_camera->GetCameraPosition();
		m_ground->MoveHeightPosition(heightPosition, 5.f);
		m_camera->CameraPositionSet(heightPosition);
	}

	// test--------------------------------------------
	m_scenes[m_sceneIndex]->Update(deltaTime);
	// ------------------------------------------------
}

void GameWorld::Render() {
	glClearColor(0.f, 0.f, 0.f , 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	WorldRendering();

	glutSwapBuffers();
}