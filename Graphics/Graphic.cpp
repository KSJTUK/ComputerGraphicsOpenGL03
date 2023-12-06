#include "pch.h"
#include "Graphics/Graphic.h"
#include "Graphics/Shader.h"
#include "Graphics/Camera.h"
#include "Model/ModelList.h"

// test--------------------------------------------
#include "Object/Cube.h"
#include "Object/LightObject.h"
#include "Util/TextureComponent.h"
#include "Graphics/Terrain.h"
#include "Graphics/SkyBox.h"
#include "Object/LightObject.h"
#include "Graphics/ParticleSystem.h"
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

		if (key == GLUT_KEY_F6) {
			m_light->StartOnOff();
		}

		if (key == GLUT_KEY_F7) {
			m_light->StopOnOff();
		}

		if (key == GLUT_KEY_F8) {
			m_camera->OnOffOrbit();
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
	m_light = std::make_unique<LightObject>("sphere", glm::vec4{ 1.f }, glm::vec3{ 0.f, 3.f, 0.f });
	m_light->SetScale(glm::vec3{ 0.2f });

	// 카메라 생성
	m_camera = std::make_unique<Camera>();
	m_camera->Init();

	m_background = std::make_unique<SkyBox>();
	m_ground = std::make_unique<Terrain>(glm::uvec2{ 20, 20 });

	auto particleGenerateArea = std::make_pair(glm::vec3{ -100.f, 100.f, -100.f }, glm::vec3{ 100.f, 100.f, 100.f });
	m_particleSystem = std::make_unique<ParticleSystem>(particleGenerateArea, 30.f, 500, 0.05f);

	m_textureCube = std::make_unique<TexturedCube>();

	m_belendedCubes.resize(5);
	for (auto& cube : m_belendedCubes) {
		cube = std::make_unique<Cube>("cube");
		cube->SetPosition(glm::linearRand(glm::vec3{ -100.f, 0.f, -100.f }, glm::vec3{ 100.f, 0.f, 100.f }));
		cube->SetObjectColor(glm::linearRand(glm::vec4{ 0.f, 0.f, 0.f, 0.5f }, glm::vec4{ 1.f, 1.f, 1.f, 0.5f }));
		cube->SetScale(glm::vec3{ 5.f, 10.f, 5.f });
		cube->AlphaBlending();
	}
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

	m_light->SetLightOption();
	m_light->SetLightOptionInTerrain();
	m_light->Render();

	m_background->Render();
	m_ground->Render();

	m_particleSystem->Render();

	m_textureCube->Render();

	for (auto& cube : m_belendedCubes) {
		cube->Render();
	}

	glViewport(0, 0, m_windowInfo->width, m_windowInfo->height);
}

void GameWorld::Init() {
	SetGLOptions();

	CreateShaderPrograms();

	InitModelList();

	CreateDefaultObjects();

	// 투영 변환 행렬 계산 및 전송
	CalcPerspectiveMat();

	m_isInited = true;
}

void GameWorld::Update(float deltaTime) {
	m_deltaTime = deltaTime;
	m_light->Update(deltaTime);

	m_camera->Update(m_deltaTime);

	m_particleSystem->Update(m_deltaTime);

	if (m_cameraMoveOnTerrain) {
		glm::vec3 heightPosition = m_camera->GetCameraPosition();
		m_ground->MoveHeightPosition(heightPosition, 10.f);
		m_camera->CameraPositionSet(heightPosition);
	}

	m_particleSystem->TerrainCollision(*(m_ground.get()));

	for (auto& cube : m_belendedCubes) {
		cube->TerrainCollision(*(m_ground.get()));
	}
}

void GameWorld::Render() {
	glClearColor(0.f, 0.f, 0.f , 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	WorldRendering();

	glutSwapBuffers();
}