#pragma once

class Object {
public:
	Object();
	virtual ~Object();

protected:
	std::shared_ptr<class Model> m_model{ };
	std::string m_modelTag{ };
	
	glm::mat4 m_initTransform{ 1.f };
	glm::mat4 m_transform{ 1.f };
	glm::mat4 m_parentTransform{ 1.f };

	glm::vec3 m_position{ };
	glm::vec3 m_rotateAngle{ };
	glm::vec3 m_scaleFactor{ 1.f };

	bool m_isDeleted{ false };

public:
	bool IsDeleted() const { return m_isDeleted; }
	glm::mat4 GetTransformMat() const { return m_transform; }

public:
	virtual void Update(float deltaTime) = 0;
	virtual void Render();

};