#include "pch.h"
#include "tank.h"
#include "Object/Cube.h"

Tank::Tank() {
	Cube* main = new Cube{ "cube" };
	Cube* loopTop = new Cube{ "cube", glm::translate(glm::mat4{ 1.f }, glm::vec3{ 0.f, 1.f ,0.f }) };
	Cube* leftMissile = new Cube{ "cylinder", glm::translate(glm::mat4{ 1.f }, glm::vec3{ -1.f, 0.f ,0.5f }) };
	Cube* rightMissile = new Cube{ "cylinder", glm::translate(glm::mat4{ 1.f }, glm::vec3{ 1.f, 0.f ,0.5f }) };
	Cube* leftHorn = new Cube{ "cylinder", glm::translate(glm::mat4{ 1.f }, glm::vec3{ -0.3f, 1.f ,0.f }) };
	Cube* rightHorn = new Cube{ "cylinder", glm::translate(glm::mat4{ 1.f }, glm::vec3{ 0.3f, 1.f ,0.f }) };


	main->SEtScale(glm::vec3{ 1.f, 1.f, 1.f });
	loopTop->SEtScale(glm::vec3{ 0.5f, 0.7f, 0.5f });

	leftMissile->SetRotate(glm::vec3{ 90.f, 0.f, 0.f });
	leftMissile->SEtScale(glm::vec3{ 0.4f, 1.f, 0.4f });

	rightMissile->SetRotate(glm::vec3{ 90.f, 0.f, 0.f });
	rightMissile->SEtScale(glm::vec3{ 0.4f, 1.f, 0.4f });

	leftHorn->SEtScale(glm::vec3{ 0.2f, 0.75f, 0.2f });
	rightHorn->SEtScale(glm::vec3{ 0.2f, 0.75f, 0.2f });

	m_tankParts.push_back(main);
	m_tankParts.push_back(loopTop);
	m_tankParts.push_back(leftMissile);
	m_tankParts.push_back(rightMissile);
	m_tankParts.push_back(leftHorn);
	m_tankParts.push_back(rightHorn);

	for (auto& part : m_tankParts) {
		part->SetObjectColor(glm::linearRand(glm::vec3{ 0.f }, glm::vec3{ 1.f }));
	}
}

Tank::Tank(const glm::vec3& initPosition) {
	m_position = initPosition;

	Cube* main = new Cube{ "cube" };
	Cube* loopTop = new Cube{ "cube", glm::translate(glm::mat4{ 1.f }, glm::vec3{ 0.f, 1.f ,0.f }) };
	Cube* leftMissile = new Cube{ "cylinder", glm::translate(glm::mat4{ 1.f }, glm::vec3{ -1.f, 0.f ,0.5f }) };
	Cube* rightMissile = new Cube{ "cylinder", glm::translate(glm::mat4{ 1.f }, glm::vec3{ 1.f, 0.f ,0.5f }) };
	Cube* leftHorn = new Cube{ "cylinder", glm::translate(glm::mat4{ 1.f }, glm::vec3{ -0.3f, 1.f ,0.f }) };
	Cube* rightHorn = new Cube{ "cylinder", glm::translate(glm::mat4{ 1.f }, glm::vec3{ 0.3f, 1.f ,0.f }) };


	main->SEtScale(glm::vec3{ 4.f, 3.f, 4.f });
	loopTop->SEtScale(glm::vec3{ 2.5f, 2.f, 2.5f });

	leftMissile->SetRotate(glm::vec3{ 90.f, 0.f, 0.f });
	leftMissile->SEtScale(glm::vec3{ 0.4f, 1.5f, 0.4f });

	rightMissile->SetRotate(glm::vec3{ 90.f, 0.f, 0.f });
	rightMissile->SEtScale(glm::vec3{ 0.4f, 1.5f, 0.4f });

	leftHorn->SEtScale(glm::vec3{ 0.2f, 1.f, 0.2f });
	rightHorn->SEtScale(glm::vec3{ 0.2f, 1.f, 0.2f });

	m_tankParts.push_back(main);
	m_tankParts.push_back(loopTop);
	m_tankParts.push_back(leftMissile);
	m_tankParts.push_back(rightMissile);
	m_tankParts.push_back(leftHorn);
	m_tankParts.push_back(rightHorn);

	for (auto& part : m_tankParts) {
		part->SetObjectColor(glm::linearRand(glm::vec3{ 0.f }, glm::vec3{ 1.f }));
	}
}

Tank::~Tank() {
	
}

void Tank::AutoMoveHorn() {
	
}

void Tank::AutoMoveMissile() {

}

void Tank::AutoRotateMissile() {

}

void Tank::Fire() {
}

void Tank::Input(unsigned char key, bool down) {
	if (down) {
		if (key == 'w') {
			for (auto& part : m_tankParts) {
			}
		}

		if (key == 'a') {

		}

		if (key == 'd') {
		}

		if (key == 's') {
		
		}
	}
}

void Tank::SpecialInput(int key, bool down) {
	if (down) {
		if (key == ' ') {
			Fire();
		}
	}
}

void Tank::Move(const glm::vec3& moveDirection) {
	m_position += moveDirection * 1.f;
}

void Tank::AutoMove(const glm::vec3& moveDirection) {
	m_direction = moveDirection;
}

void Tank::Update(float deltaTime) {
	m_deltaTime = deltaTime;
	for (auto& part : m_tankParts) {
		part->Update(m_deltaTime);

		if (m_autoMoveMode) {
		}
	}
}

void Tank::Render() {
	for (auto& part : m_tankParts) {
		part->Render();
	}
}