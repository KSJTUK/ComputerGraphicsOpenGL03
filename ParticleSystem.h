#pragma once


struct Particle {
	glm::vec3 position{ };
	glm::vec2 texture{ };
	glm::vec4 color{ };

	glm::vec3 speed{ };
	float lifeTime{ };
};


class ParticleSystem {
public:
	ParticleSystem();
	ParticleSystem(float lifeTime, int maxCountParticles);
	ParticleSystem(float lifeTime, int maxCountParticles, float createTime);
	ParticleSystem(std::pair<glm::vec3, glm::vec3>& generateParticleArea, float lifeTime, int maxCountParticles, float createTime);
	ParticleSystem(std::pair<glm::vec3, glm::vec3>& generateParticleArea, float lifeTime, int maxCountParticles, float createTime,
		float primitiveSize, bool randValues = false);
	~ParticleSystem();

private:
	const float gravity{ 9.8f };
	const float endGravitySpeed{ 5.f };

private:
	std::vector<Particle> m_particles{ };

	// 렌더링 관련 변수
	unsigned int m_particleVAO{ };
	unsigned int m_particleVBO{ };
	int m_particleDrawMode{ GL_POINTS };
	float m_primitiveSize{ 4.0f };

	float m_timeElapsed{ };
	float m_randSpeedTime{ };

	float m_deltaTime{ };
	
	// 
	std::pair<glm::vec3, glm::vec3> m_particleGenerateArea{ };
	float m_newParticleCreateTime{ 1.f };
	float m_particlesLifeTime{ 5.f };
	int m_maxCountParticle{ 100 };

private:
	void CreateNewParticle();
	void ParticleUpdate(Particle& particle);
	void RemoveLifeEndParticles();
	void SetParticleVertexs();

	void SetPerspectiveMatrix(const glm::mat4& perspectiveMatrix);

public:
	void Update(float deltaTime);
	void Render();
};