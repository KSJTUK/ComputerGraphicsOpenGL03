#include "pch.h"
#include "Graphics/Graphic.h"
#include "Graphics/Shader.h"
#include "Graphics/Camera.h"

Graphics::Graphics() { }

Graphics::~Graphics() { }

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
	SHADER->UnUseProgram();
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

	// ���̴� ���α׷��� ���� ���� ����, ��ĵ��� ���, ������ �� �ֵ��� ���α׷� ��� ����
	SHADER->UseProgram();

	// ī�޶� ����
	m_camera = std::make_unique<Camera>();
	m_camera->Init();

	// �𵨸���Ʈ�� �����ϰ� �� �ҷ�����
	//ModelList::GetInst()->Init(SHADER->GetShaderProgramID());

	// ���� ��ȯ ��� ��� �� ����
	SetPerspectiveMat();
	// ���̴� ���α׷� ��� ����
	SHADER->UnUseProgram();

	m_isInited = true;
}

void Graphics::Update(float deltaTime) {
	m_deltaTime = deltaTime;
	m_camera->Update(m_deltaTime);
}

void Graphics::Render() {
	glClearColor(0.5f, 0.5f, 0.5f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, m_windowInfo->width, m_windowInfo->height);

	glutSwapBuffers();
}