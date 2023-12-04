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
// ------------------------------------------------

GameWorld::GameWorld() { }

GameWorld::~GameWorld() { }

bool GameWorld::IsInited() const {
	return m_isInited;
}

void GameWorld::SetWindowInfo(std::shared_ptr<struct WindowInfo>& winInfo) {
	m_windowInfo = winInfo;
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
			OBJECTSHADER->UseProgram();
			OBJECTSHADER->UnUseProgram();
		}

		if (key == GLUT_KEY_F2) {
			OBJECTSHADER->UseProgram();
			OBJECTSHADER->UnUseProgram();
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
}

void GameWorld::CreateDefaultObjects() {
	// 카메라 생성
	m_camera = std::make_unique<Camera>();
	m_camera->Init();

	m_background = std::make_unique<SkyBox>();
	m_ground = std::make_unique<Terrain>(glm::uvec2{ 20, 20 });
}

void GameWorld::SetPerspectiveAllShader() {
	BACKGROUNDSHADER->SetUniformMat4("perspectiveMat", m_perspectiveMatrix);
	TERRAINSHADER->SetUniformMat4("perspectiveMat", m_perspectiveMatrix);
	PARTICLESHADER->SetUniformMat4("perspectiveMat", m_perspectiveMatrix);
	OBJECTSHADER->SetUniformMat4("perspectiveMat", m_perspectiveMatrix);
	LIGHTOBJECTSHADER->SetUniformMat4("perspective", m_perspectiveMatrix);
}

void GameWorld::SetViewMatAllShader(const glm::mat4& viewMat) {
	BACKGROUNDSHADER->SetUniformMat4("viewMat", glm::mat4(glm::mat3(viewMat)));
	TERRAINSHADER->SetUniformMat4("viewMat", viewMat);
	PARTICLESHADER->SetUniformMat4("viewMat", viewMat);
	OBJECTSHADER->SetUniformMat4("viewMat", viewMat);
	LIGHTOBJECTSHADER->SetUniformMat4("view", viewMat);
}

void GameWorld::WorldRendering() {
	m_camera->Render();
	SetViewMatAllShader(m_camera->GetViewMat());

	m_background->Render();
	m_ground->Render();
	m_scenes[m_sceneIndex]->Render();

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
	m_camera->Update(m_deltaTime);

	glm::vec3 heightPosition = m_camera->GetCameraPosition();
	m_ground->MoveHeightPosition(heightPosition, 2.f);
	m_camera->CameraPositionSet(heightPosition);

	// test--------------------------------------------
	m_scenes[m_sceneIndex]->Update(deltaTime);
	// ------------------------------------------------
}

void GameWorld::Render() {
	glClearColor(1.f, 1.f, 1.f , 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	WorldRendering();

	glutSwapBuffers();
}