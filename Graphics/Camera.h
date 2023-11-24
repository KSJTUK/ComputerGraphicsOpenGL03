#pragma once

class Camera {
public:
	Camera() { }
	~Camera() { }

private:
	// ī�޶��� ���� �Ķ����
	glm::vec3 m_EYE{ 0.f, 0.f, 3.f };
	glm::vec3 m_AT{ 0.f, 0.f, -1.f };
	glm::vec3 m_UP{ 0.f, 1.f, 0.f };

	// �亯ȯ ���
	glm::mat4 m_view{ 1.f };

	// ī�޶� ������Ʈ�� ���� �ð� �� ����
	float m_deltaTime{ };

	// ī�޶� �������� ���� ������
	float m_moveSpeed{ 1000.f };
	float m_angleSpeed{ 3.f };

	float m_fixAt{ 1.f };

	// ī�޶� ������ ����, ī�޶��� �� ���� ���͵��� ������ ����
	glm::vec3 m_cameraAxisX{ };
	glm::vec3 m_cameraAxisY{ };
	glm::vec3 m_cameraAxisZ{ };

	float m_cameraAngleX{ };
	float m_cameraAngleY{ };

	int m_rotateY{ 0 };
	int m_orbitY{ 0 };

	bool m_spotLightingOn{ false };

public:
	// getter
	const glm::mat4& GetViewMat() const;

	// setter
	void CameraPositionSet(const glm::vec3& position);
	void CameraViewPointSet(const glm::vec3& at);
	void CameraMoveSpeedSet(const float& speed);

	float GetCameraAngleX() const { return m_cameraAngleX; }
	float GetCameraAngleY() const { return m_cameraAngleY; }

	void ViewPointFix();
	void ViewPointUnFix();

	void CameraPositionRotateX(const float& angle, const glm::vec3& center);

public:
	// �ܺ� Ű�Է��� ī�޶� ��ü������ ó���ϰ� ��
	void Input(unsigned char key, bool down);
	void SpecialInput(int key, bool down);
	void MouseMotionInput(int x, int y, int prevX, int prevY);
	void MousePassiveMotionInput(int x, int y, int prevX, int prevY);

	void Move(const glm::vec3& moveVec);
	void ViewPointMove(float moveAngle, const glm::vec3& axis);

public:
	void Init();
	void Update(float deltaTime);
	void Render();
};

