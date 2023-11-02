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

	glm::vec3 m_lightColor{ 1.f };
	glm::vec3 m_objectColor{ };

	glm::vec3 m_direction{ 0.f, 0.f, 1.f };

	bool m_isDeleted{ false };

public:
	void SetInitMat(const glm::mat4& init) { m_initTransform = init; }

	void SetPosition(const glm::vec3& position) { m_position = position; }
	void SetRotate(const glm::vec3& rotateAngle) { m_rotateAngle = rotateAngle; }
	void SEtScale(const glm::vec3& scaleFactor) { m_scaleFactor = scaleFactor; };

	void Delete() { m_isDeleted = true; }

public:
	bool IsDeleted() const { return m_isDeleted; }
	glm::mat4 GetTransformMat() const { return m_transform; }

public:
	virtual void Update(float deltaTime) = 0;
	virtual void Render();

};