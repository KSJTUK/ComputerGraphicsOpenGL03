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

GameWorld::~GameWorld() {
	// test--------------------------------------------
	if (m_cube) delete m_cube;
	// ------------------------------------------------

}

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

void GameWorld::Init() {
	// 쉐이더 프로그램 생성
	OBJECTSHADER->CreateShaderProgram();
	LIGHTOBJECTSHADER->CreateShaderProgram();
	PARTICLESHADER->CreateShaderProgram();
	TERRAINSHADER->CreateShaderProgram();
	BACKGROUNDSHADER->CreateShaderProgram();
	// 쉐이더 프로그램이 각종 정점 정보, 행렬들을 등록, 전송할 수 있도록 프로그램 사용 설정
	OBJECTSHADER->UseProgram();

	glPointSize(2.f);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// 카메라 생성
	m_camera = std::make_unique<Camera>();
	m_camera->Init();

	BACKGROUNDSHADER->UseProgram();
	m_background = std::make_unique<SkyBox>();
	BACKGROUNDSHADER->UnUseProgram();

	TERRAINSHADER->UseProgram();
	m_ground = std::make_unique<Terrain>(glm::uvec2{ 20, 20 });
	TERRAINSHADER->UnUseProgram();

	// 모델리스트를 생성하고 모델 불러오기
	MODELLIST->Init();
	MODELLIST->LoadModel("cube.obj");
	MODELLIST->LoadModel("cone.obj");
	MODELLIST->LoadModel("sphere.obj");
	MODELLIST->LoadModel("cylinder.obj");
	MODELLIST->LoadModel("earth.obj", "Earth_diffuse_512p.png");

	// test--------------------------------------------
	m_scenes.push_back(new WorldScene1{ });
	// ------------------------------------------------

	for (auto& scene : m_scenes) {
		scene->Init();
	}


	// 투영 변환 행렬 계산 및 전송
	CalcPerspectiveMat();

	m_isInited = true;
	// 쉐이더 프로그램 사용 종료

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	OBJECTSHADER->UnUseProgram();
}

void GameWorld::Update(float deltaTime) {
	m_deltaTime = deltaTime;
	m_camera->Update(m_deltaTime);

	glm::vec3 heightPosition = m_camera->GetCameraPosition();
	m_ground->MoveHeightPosition(heightPosition);
	m_camera->CameraPositionSet(heightPosition);
	// test--------------------------------------------
	m_scenes[m_sceneIndex]->Update(deltaTime);
	// ------------------------------------------------
}

void GameWorld::Render() {

	glClearColor(1.f, 1.f, 1.f , 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_camera->Render();
	glm::mat4 cameraViewMatrix{ m_camera->GetViewMat() };

	BACKGROUNDSHADER->UseProgram();
	BACKGROUNDSHADER->SetUniformMat4("perspectiveMat", m_perspectiveMatrix);
	BACKGROUNDSHADER->SetUniformMat4("viewMat", glm::mat4(glm::mat3(cameraViewMatrix)));
	BACKGROUNDSHADER->UnUseProgram();

	TERRAINSHADER->UseProgram();
	TERRAINSHADER->SetUniformMat4("perspectiveMat", m_perspectiveMatrix);
	TERRAINSHADER->SetUniformMat4("viewMat", cameraViewMatrix);
	TERRAINSHADER->UnUseProgram();

	PARTICLESHADER->UseProgram();
	PARTICLESHADER->SetUniformMat4("perspectiveMat", m_perspectiveMatrix);
	PARTICLESHADER->SetUniformMat4("viewMat", cameraViewMatrix);
	PARTICLESHADER->UnUseProgram();

	OBJECTSHADER->UseProgram();
	OBJECTSHADER->SetUniformMat4("perspectiveMat", m_perspectiveMatrix);
	OBJECTSHADER->SetUniformMat4("viewMat", cameraViewMatrix);
	OBJECTSHADER->UnUseProgram();

	LIGHTOBJECTSHADER->UseProgram();
	LIGHTOBJECTSHADER->SetUniformMat4("perspective", m_perspectiveMatrix);
	LIGHTOBJECTSHADER->SetUniformMat4("view", cameraViewMatrix);
	LIGHTOBJECTSHADER->UnUseProgram();

	BACKGROUNDSHADER->UseProgram();
	m_background->Render();
	BACKGROUNDSHADER->UnUseProgram();

	TERRAINSHADER->UseProgram();
	m_ground->Render();
	TERRAINSHADER->UnUseProgram();

	m_scenes[m_sceneIndex]->Render();


	glViewport(0, 0, m_windowInfo->width, m_windowInfo->height);

	glutSwapBuffers();
}