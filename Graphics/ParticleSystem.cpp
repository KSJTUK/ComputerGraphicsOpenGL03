#include "pch.h"
#include "ParticleSystem.h"
#include "Graphics/Shader.h"

ParticleSystem::ParticleSystem() {
	PARTICLESHADER->UseProgram();
	//glPointSize(m_primitiveSize);
	glGenVertexArrays(1, &m_particleVAO);
	glGenBuffers(1, &m_particleVBO);

	glBindVertexArray(m_particleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_particleVBO);
	PARTICLESHADER->UnUseProgram();
}

ParticleSystem::ParticleSystem(float lifeTime, int maxCountParticles)
	: m_particlesLifeTime{ lifeTime }, m_maxCountParticle{ maxCountParticles } {
	PARTICLESHADER->UseProgram();
	//glPointSize(m_primitiveSize);
	glGenVertexArrays(1, &m_particleVAO);
	glGenBuffers(1, &m_particleVBO);

	glBindVertexArray(m_particleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_particleVBO);
	PARTICLESHADER->UnUseProgram();
}

ParticleSystem::ParticleSystem(float lifeTime, int maxCountParticles, float createTime)
	:m_particlesLifeTime{ lifeTime }, m_maxCountParticle{ maxCountParticles }, m_newParticleCreateTime{ createTime } {
	PARTICLESHADER->UseProgram();
	//glPointSize(m_primitiveSize);
	glGenVertexArrays(1, &m_particleVAO);
	glGenBuffers(1, &m_particleVBO);

	glBindVertexArray(m_particleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_particleVBO);
	PARTICLESHADER->UnUseProgram();
}

ParticleSystem::ParticleSystem(std::pair<glm::vec3, glm::vec3>& generateParticleArea, float lifeTime, int maxCountParticles, float createTime)
	: m_particleGenerateArea{ generateParticleArea }, m_particlesLifeTime{ lifeTime },
	m_maxCountParticle{ maxCountParticles }, m_newParticleCreateTime{ createTime } {
	//glPointSize(m_primitiveSize);
	PARTICLESHADER->UseProgram();
	glGenVertexArrays(1, &m_particleVAO);
	glGenBuffers(1, &m_particleVBO);

	glBindVertexArray(m_particleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_particleVBO);
	PARTICLESHADER->UnUseProgram();
}

ParticleSystem::~ParticleSystem() {
	glDeleteBuffers(1, &m_particleVBO);
	glDeleteVertexArrays(1, &m_particleVAO);
}

void ParticleSystem::CreateNewParticle() {
	glm::vec3 generatePosition{ glm::linearRand(m_particleGenerateArea.first, m_particleGenerateArea.second) };
	glm::vec4 particleColor{ 1.f };
	glm::vec3 defaultSpeed{ 0.f };
	float randomLife{ glm::linearRand(2.f, m_particlesLifeTime) };

	m_particles.push_back(Particle{
		generatePosition,
		{ },
		particleColor,
		defaultSpeed,
		randomLife
		});
}

void ParticleSystem::ParticleUpdate(Particle& particle) {
	particle.lifeTime -= m_deltaTime;
	m_randSpeedTime += m_deltaTime;

	if (particle.speed.y > -endGravitySpeed) {
		particle.speed.y -= gravity * m_deltaTime;
	}

	particle.position += particle.speed * m_deltaTime;
	if (particle.position.y < -2.5f) {
		particle.position.y = -2.5f;
		particle.speed.x = 0.f;
		particle.speed.z = 0.f;
		return;
	}

	if (m_randSpeedTime > 2.f) {
		m_randSpeedTime = 0.0f;
		particle.speed.x = glm::linearRand(-10.f, 10.f);
		particle.speed.z = glm::linearRand(-10.f, 10.f);
	}
}

void ParticleSystem::RemoveLifeEndParticles() {
	auto iter = m_particles.begin();
	while (iter != m_particles.end()) {
		if ((*iter).lifeTime <= 0.f) {
			iter = m_particles.erase(iter);
			continue;
		}
		++iter;
	}
}

void ParticleSystem::SetParticleVertexs() {
	glDeleteBuffers(1, &m_particleVBO);
	glDeleteVertexArrays(1, &m_particleVAO);

	glGenVertexArrays(1, &m_particleVAO);
	glGenBuffers(1, &m_particleVBO);

	glBindVertexArray(m_particleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_particleVBO);

	glBufferData(GL_ARRAY_BUFFER, m_particles.size() * sizeof(Particle), &m_particles[0], GL_STATIC_DRAW);

	// location 0번에 Particle객체의 position정보를 넘겨줌
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, position));
	glEnableVertexAttribArray(0);

	// location 1번에 Particle객체의 texture정보를 넘겨줌
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, texture));
	glEnableVertexAttribArray(1);

	// location 2번에 Particle객체의 color정보를 넘겨줌
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, color));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void ParticleSystem::DecGenerateTime() {
	if (abs(m_newParticleCreateTime) < 0.00001f) {
		m_newParticleCreateTime = 0.001f;
	}
	m_newParticleCreateTime -= 0.01f;
}

void ParticleSystem::IncGenerateTime() {
	m_newParticleCreateTime += 0.01f;
}

void ParticleSystem::Update(float deltaTime) {
	PARTICLESHADER->UseProgram();

	m_deltaTime = deltaTime;

	if (m_timeElapsed > m_newParticleCreateTime) {
		m_timeElapsed = 0.f;
		CreateNewParticle();
	}

	for (auto& particle : m_particles) {
		ParticleUpdate(particle);
	}

	RemoveLifeEndParticles();

	if (!m_particles.empty()) {
		SetParticleVertexs();
	}
	m_timeElapsed += deltaTime;

	PARTICLESHADER->UnUseProgram();
}

void ParticleSystem::Render() {
	PARTICLESHADER->UseProgram();
	glBindVertexArray(m_particleVAO);
	glDrawArrays(m_particleDrawMode, 0, uint32(m_particles.size()));
	glBindVertexArray(0);
	PARTICLESHADER->UnUseProgram();
}
