#include "pch.h"
#include "Util/Engine.h"
#include "Util/callbacks.h"
#include "Util/Timer.h"
#include "Graphics/Graphic.h"

Engine::Engine() {
	m_windowInfo = std::make_shared<WindowInfo>();

	m_windowInfo->x = 100;
	m_windowInfo->y = 100;
	m_windowInfo->width = 800;
	m_windowInfo->height = 600;
	m_windowInfo->fWidth = static_cast<float>(m_windowInfo->width);
	m_windowInfo->fHeight = static_cast<float>(m_windowInfo->height);

	std::string title{ "OpenGL Project 03" };
	std::string::size_type size = title.size();
	m_windowInfo->windowTitle = new char[size + 1] {};
	memcpy(m_windowInfo->windowTitle, title.c_str(), size + 1);
}

Engine::~Engine() {
	// �����Ҵ� ��ü�� �޸� �Ҵ� ����
	if (m_windowInfo->windowTitle) {
		delete[] m_windowInfo->windowTitle;
	}
}

// �ݹ��Լ��� ���
void Engine::SubscribeCallbacks() {
	glutDisplayFunc(renderFunc);
	glutReshapeFunc(reshapeFunc);
	glutKeyboardFunc(keyboardFunc);
	glutKeyboardUpFunc(keyboardUpFunc);
	glutMouseFunc(mouseFunc);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mousePassiveMotion);
	glutIdleFunc(idleFunc);
	glutSpecialFunc(specialkeyFunc);
	glutSpecialUpFunc(specialKeyUpFunc);
}

size_t Engine::GetWindowWidth() const {
	return m_windowInfo->width;
}

size_t Engine::GetWindowHeight() const {
	return m_windowInfo->height;
}

float Engine::GetWindowWidthF() const {
	return m_windowInfo->fWidth;
}

float Engine::GetWindowHeightF() const {
	return m_windowInfo->fHeight;
}

void Engine::SetWindowSize(int32 windowWidth, int32 windowHeight) {
	m_windowInfo->width = static_cast<size_t>(windowWidth);
	m_windowInfo->height = static_cast<size_t>(windowHeight);
	m_windowInfo->fWidth = static_cast<float>(windowWidth);
	m_windowInfo->fHeight = static_cast<float>(windowHeight);
}


void Engine::Init(int32* argc, char** argv) {
	// glut���̺귯�� �ʱ�ȭ
	glutInit(argc, argv);

	// ������ ��¸�� ����(������۸�, RGBA, ���̹���)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	// ������ ũ��, ��ǥ ����
	glutInitWindowPosition(m_windowInfo->x, m_windowInfo->y);
	glutInitWindowSize(m_windowInfo->width, m_windowInfo->height);

	// ������ ����
	glutCreateWindow(m_windowInfo->windowTitle);

	// glew ���̺귯�� �ʱ�ȭ
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		throw "GLEW ���̺귯�� �ʱ�ȭ ����";
	}

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	SubscribeCallbacks();

	//((bool(__stdcall*)(int))wglGetProcAddress("wglSwapIntervalEXT"))(0); // ���� ����ȭ

	// Ÿ�̸� �ʱ�ȭ
	m_timer = std::make_unique<Timer>();
	m_timer->Init();

	m_grapics = std::make_unique<Graphics>();
	m_grapics->SetWindowInfo(m_windowInfo);
	m_grapics->Init();
}

void Engine::ReSizeWindow(int32 w, int32 h) {
	m_windowInfo->width = w;
	m_windowInfo->height = h;
	m_windowInfo->fWidth = static_cast<float>(m_windowInfo->width);
	m_windowInfo->fHeight = static_cast<float>(m_windowInfo->height);

	if (m_grapics->IsInited()) {
		m_grapics->SetWindowInfo(m_windowInfo);
	}
}

void Engine::Update() {
	m_timer->Update();
	m_deltaTime = m_timer->GetDeltaTime();
	float fps = m_timer->GetFrame();
	//std::cout << m_deltaTime << "   " << fps << "\n";
	m_grapics->Update(m_deltaTime);
}

void Engine::Render() {
	m_grapics->Render();
}

void Engine::Input(unsigned char key, bool down) {
	m_grapics->Input(key, down);
}

void Engine::SpecialInput(int32 key, bool down) {
	m_grapics->SpecialInput(key, down);
}

void Engine::MouseMotionInput(int32 x, int32 y) {
	m_grapics->MouseMotionInput(x, y, m_mousePrevPos[0], m_mousePrevPos[1]);
	m_mousePrevPos[0] = x;
	m_mousePrevPos[1] = y;
}

void Engine::MousePassiveMotionInpit(int32 x, int32 y) {
	m_mousePrevPos[0] = x;
	m_mousePrevPos[1] = y;
}


// --------------------------------------------------------------------
void Engine::SubscribeMouseMotionFunc(void(*func)(int, int)) {
	glutMotionFunc(func);
}

void Engine::SubscribeDrawFunc(void(*func)(void)) {
	glutDisplayFunc(func);
}

void Engine::SubscribeMouseFunc(void(*func)(int, int, int, int)) {
	glutMouseFunc(func);
}

void Engine::SubscribeKeyboardUpfunc(void(*func)(unsigned char, int, int)) {
	glutKeyboardUpFunc(func);
}

void Engine::SubscribePassiveMotionFunc(void(*func)(int, int)) {
	glutPassiveMotionFunc(func);
}

void Engine::SubscribeKeyboardFunc(void(*func)(unsigned char, int, int)) {
	glutKeyboardFunc(func);
}

void Engine::SubscribeReshapeFunc(void(*func)(int, int)) {
	glutReshapeFunc(func);
}

void Engine::SubscribeIdleFUnc(void(*func)(void)) {
	glutIdleFunc(func);
}

void Engine::Loop() {
	glutMainLoop();
}

void Engine::LoopEnd() {
	glutLeaveMainLoop();
}
