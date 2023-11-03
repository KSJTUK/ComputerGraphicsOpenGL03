#include "pch.h"
#include "Shader.h"
#include "Graphics/Camera.h"

const glm::mat4& Camera::GetViewMat() const {
	return m_view;
}

void Camera::CameraPositionSet(const glm::vec3& position) {
	m_EYE = position;
}

void Camera::CameraViewPointSet(const glm::vec3& at) {
	m_AT = at;
	if (m_AT == glm::vec3{ 0.f }) {
		m_AT = glm::vec3{ 0.f, 0.f, 1.f };
	}
}

void Camera::CameraMoveSpeedSet(const float& speed) {
	m_moveSpeed = speed;
}

void Camera::ViewPointFix() {
	m_fixAt = 0.f;
}

void Camera::ViewPointUnFix() {
	m_fixAt = 1.f;
}

void Camera::CameraPositionRotateX(const float& angle, const glm::vec3& center) {
	//ObjectMove::OrbitMove(m_EYE, angle, ObjectMove::axisY, center);
}

void Camera::Input(unsigned char key, bool down) {
	switch (key) {
	case 'm':
		Move(m_cameraAxisY);
		break;

	case 'n':
		Move(-m_cameraAxisY);
		break;

	case 'v':
		if (m_fixAt > 0.f) {
			ViewPointFix();
		}
		else {
			ViewPointUnFix();
		}
	}
}

void Camera::SpecialInput(int key, bool down) {
	switch (key) {
	case GLUT_KEY_RIGHT:
		Move(m_cameraAxisX);
		break;

	case GLUT_KEY_LEFT:
		Move(-m_cameraAxisX);
		break;

	case GLUT_KEY_UP:
		Move(-m_cameraAxisZ);
		break;

	case GLUT_KEY_DOWN:
		Move(m_cameraAxisZ);
		break;
	}
}

void Camera::MouseMotionInput(int x, int y, int prevX, int prevY) {
	float angleX{ -(x - prevX) / m_angleSpeed };
	ViewPointMove(angleX, m_cameraAxisY);
	m_cameraAngleX += angleX;

	if (m_cameraAngleY > -90.f and m_cameraAngleY < 90.f) {
		float angleY{ -(y - prevY) / m_angleSpeed };
		ViewPointMove(angleY, m_cameraAxisX);
		m_cameraAngleY += angleY;
	}
	else if (m_cameraAngleY <= -90.f) {
		m_cameraAngleY = -89.f;
	}
	else if (m_cameraAngleY >= 90.f) {
		m_cameraAngleY = 89.f;
	}
}

void Camera::MousePassiveMotionInput(int x, int y, int prevX, int prevY) {
	//float angleX{ -(x - prevX) / m_angleSpeed };
	//ViewPointMove(angleX, m_cameraAxisY);
	//m_cameraAngleX += angleX;

	//if (m_cameraAngleY > -90.f and m_cameraAngleY < 90.f) {
	//	float angleY{ -(y - prevY) / m_angleSpeed };
	//	ViewPointMove(angleY, m_cameraAxisX);
	//	m_cameraAngleY += angleY;
	//}
	//else if (m_cameraAngleY <= -90.f) {
	//	m_cameraAngleY = -89.f;
	//}
	//else if (m_cameraAngleY >= 90.f) {
	//	m_cameraAngleY = 89.f;
	//}
}

void Camera::Move(const glm::vec3& moveVec) {
	glm::vec3 m = moveVec * m_moveSpeed * m_deltaTime;
	m_EYE += m;
}

void Camera::ViewPointMove(float moveAngle, const glm::vec3& axis) {
	glm::vec4 at{ m_AT, 1.f };
	m_AT = glm::normalize(glm::rotate(m_AT, glm::radians(moveAngle), axis));
}

void Camera::Init() {

}

void Camera::Update(float deltaTime) {
	m_deltaTime = deltaTime;

	// 카메라 기저 계산 순서 -> n, u, v -> 카메라 z, x, y축
	m_cameraAxisZ = glm::normalize(-m_AT);
	m_cameraAxisX = glm::normalize(glm::cross(m_UP, m_cameraAxisZ));
	m_cameraAxisY = glm::normalize(glm::cross(m_cameraAxisZ, m_cameraAxisX));

	SHADER->SetUniformVec3("viewPosition", m_EYE);
}

void Camera::Render() {
	m_view = glm::lookAt(m_EYE, m_EYE + m_AT, m_UP);
}