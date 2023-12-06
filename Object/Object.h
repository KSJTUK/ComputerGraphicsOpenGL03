#pragma once

class Object {
public:
	Object();
	Object(const std::string& modelTag);
	Object(const std::string& modelTag, const glm::vec4& objectColor);
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

	glm::vec4 m_objectColor{ 1.f };

	glm::vec3 m_direction{ 0.f, 0.f, 1.f };

	Meterial m_meterial{ };

	bool m_isDeleted{ false };

	float m_terrainOffset{ };

public:
	void SetMeterials();
	bool ExistTexture() const;
	void SetObjectColor(const glm::vec4& color);
	std::string GetModelTag() const { return m_modelTag; }

public:
	void SetInitMat(const glm::mat4& init) { m_initTransform = init; }

	void SetPosition(const glm::vec3& position) { m_position = position; }
	void SetRotate(const glm::vec3& rotateAngle) { m_rotateAngle = rotateAngle; }
	void SetScale(const glm::vec3& scaleFactor);

	void Delete() { m_isDeleted = true; }

	void TerrainCollision(class Terrain& terrain);

public:
	bool IsDeleted() const { return m_isDeleted; }
	glm::mat4 GetTransformMat() const { return m_transform; }
	glm::vec3 GetPosition() const { return m_position; }

public:
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;

};