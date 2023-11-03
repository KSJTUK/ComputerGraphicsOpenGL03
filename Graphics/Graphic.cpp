#include "pch.h"
#include "Graphics/Graphic.h"
#include "Graphics/Shader.h"
#include "Graphics/Camera.h"
#include "Model/ModelList.h"

// test--------------------------------------------
#include "Object/Cube.h"
#include "Object/LightObject.h"
// ------------------------------------------------

Graphics::Graphics() { }

Graphics::~Graphics() {
	// test--------------------------------------------
	if (m_cube) delete m_cube;
	// ------------------------------------------------

}

bool Graphics::IsInited() const {
	return m_isInited;
}

void Graphics::SetWindowInfo(std::shared_ptr<struct WindowInfo>& winInfo) {
	m_windowInfo = winInfo;
	SetPerspectiveMat();
}

void Graphics::SetPerspectiveMat() {
	if (!m_isInited) {
		return;
	}

	float aspect = m_windowInfo->fWidth / m_windowInfo->fHeight;
	float halfFovy = m_fovy / 2.f;

	SHADER->SetPerspectiveMat(glm::perspective(glm::radians(halfFovy), aspect, m_near, m_far));
}

void Graphics::Input(unsigned char key, bool down) {
	m_camera->Input(key, down);
}

void Graphics::SpecialInput(int key, bool down) {
}

void Graphics::MouseMotionInput(int x, int y, int prevX, int prevY) {
	m_camera->MouseMotionInput(x, y, prevX, prevY);
}

void Graphics::MousePassiveMotionInput(int x, int y, int prevX, int prevY) {
}

void Graphics::Init() {
	// 쉐이더 프로그램 생성
	SHADER->CreateShaderProgram();

	// 쉐이더 프로그램이 각종 정점 정보, 행렬들을 등록, 전송할 수 있도록 프로그램 사용 설정
	SHADER->UseProgram();

	// 카메라 생성
	m_camera = std::make_unique<Camera>();
	m_camera->Init();

	// 모델리스트를 생성하고 모델 불러오기
	MODELLIST->Init(SHADER->GetShaderProgramID());
	MODELLIST->LoadModel("cube.obj");
	MODELLIST->LoadModel("sphere.obj");

	// test--------------------------------------------
	m_cube = new Cube{ };
	m_lightObj = new LightObject{ };
	// ------------------------------------------------

	// 투영 변환 행렬 계산 및 전송
	// 쉐이더 프로그램 사용 종료

	m_isInited = true;

	SetPerspectiveMat();

	SHADER->UnUseProgram();
}

void Graphics::Update(float deltaTime) {
	m_deltaTime = deltaTime;
	m_camera->Update(m_deltaTime);
	// test--------------------------------------------
	m_lightObj->Update(m_deltaTime);
	// ------------------------------------------------
}

void Graphics::Render() {

	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SHADER->UseProgram();

	m_lightObj->SetLightOption();

	m_camera->Render();
	SHADER->SetViewMat(m_camera->GetViewMat());

	m_cube->Render();

	glViewport(0, 0, m_windowInfo->width, m_windowInfo->height);

	SHADER->UnUseProgram();


	glutSwapBuffers();
}