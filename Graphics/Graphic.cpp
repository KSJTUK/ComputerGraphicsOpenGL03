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
	CalcPerspectiveMat();
}

void Graphics::CalcPerspectiveMat() {
	if (!m_isInited) {
		return;
	}

	float aspect = m_windowInfo->fWidth / m_windowInfo->fHeight;
	float halfFovy = m_fovy / 2.f;

	m_perspectiveMatrix = glm::perspective(glm::radians(halfFovy), aspect, m_near, m_far);
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
	// ���̴� ���α׷� ����
	SHADER->CreateShaderProgram();
	LIGHTOBJECTSHADER->CreateShaderProgram();
	// ���̴� ���α׷��� ���� ���� ����, ��ĵ��� ���, ������ �� �ֵ��� ���α׷� ��� ����
	SHADER->UseProgram();

	// ī�޶� ����
	m_camera = std::make_unique<Camera>();
	m_camera->Init();

	// �𵨸���Ʈ�� �����ϰ� �� �ҷ�����
	MODELLIST->Init();
	MODELLIST->LoadModel("cube.obj");
	MODELLIST->LoadModel("sphere.obj");

	// test--------------------------------------------
	m_cube = new Cube{ };
	m_cube->SEtScale(glm::vec3{ 0.6f, 0.6f, 0.6f });
	// ------------------------------------------------

	// ���� ��ȯ ��� ��� �� ����
	CalcPerspectiveMat();

	m_isInited = true;
	// ���̴� ���α׷� ��� ����
	SHADER->UnUseProgram();

	LIGHTOBJECTSHADER->UseProgram();
	m_lightObj = new LightObject{ "sphere", glm::vec3{ 1.f, 0.5f, 0.f } };
	m_lightObj->SEtScale(glm::vec3{ 1.f, 1.f, 1.f });
	LIGHTOBJECTSHADER->UnUseProgram();
}

void Graphics::Update(float deltaTime) {
	m_deltaTime = deltaTime;
	m_camera->Update(m_deltaTime);
	// test--------------------------------------------
	m_cube->Update(m_deltaTime);
	m_lightObj->Update(m_deltaTime);
	// ------------------------------------------------
}

void Graphics::Render() {

	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_camera->Render();
	glm::mat4 cameraViewMatrix{ m_camera->GetViewMat() };

	SHADER->UseProgram();
	SHADER->SetPerspectiveMat(m_perspectiveMatrix);
	SHADER->SetViewMat(cameraViewMatrix);

	m_lightObj->SetLightOption();

	m_cube->Render();

	SHADER->UnUseProgram();

	LIGHTOBJECTSHADER->UseProgram();
	LIGHTOBJECTSHADER->SetPerspectiveMat(m_perspectiveMatrix);
	LIGHTOBJECTSHADER->SetViewMat(cameraViewMatrix);
	
	m_lightObj->Render();

	LIGHTOBJECTSHADER->UnUseProgram();

	glViewport(0, 0, m_windowInfo->width, m_windowInfo->height);

	glutSwapBuffers();
}