#include "pch.h"
#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() { 
	glGenBuffers(1, &m_particleVBO);
	glGenVertexArrays(1, &m_particleVAO);

	glBindVertexArray(m_particleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_particleVBO);
}

ParticleSystem::ParticleSystem(float lifeTime, int maxCountParticles) 
	: m_particlesLifeTime{ lifeTime }, m_maxCountParticle{ maxCountParticles }, m_particleDrawMode{ GL_POINTS } {
	glGenBuffers(1, &m_particleVBO);
	glGenVertexArrays(1, &m_particleVAO);

	glBindVertexArray(m_particleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_particleVBO);
}

ParticleSystem::ParticleSystem(float lifeTime, int maxCountParticles, float createTime) 
	:m_particlesLifeTime{ lifeTime }, m_maxCountParticle{ maxCountParticles }, m_newParticleCreateTime{ createTime } {
	glGenBuffers(1, &m_particleVBO);
	glGenVertexArrays(1, &m_particleVAO);

	glBindVertexArray(m_particleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_particleVBO);
}

ParticleSystem::ParticleSystem(std::pair<glm::vec3, glm::vec3>& generateParticleArea, float lifeTime, int maxCountParticles, float createTime) 
	: m_particlesLifeTime{ lifeTime }, m_maxCountParticle{ maxCountParticles }, m_newParticleCreateTime{ createTime } {

}

ParticleSystem::~ParticleSystem() { 
	glDeleteBuffers(1, &m_particleVBO);
	glDeleteVertexArrays(1, &m_particleVAO);
}

void ParticleSystem::CreateNewParticle() {
	glm::vec3 generatePosition{ glm::linearRand(m_particleGenerateArea.first, m_particleGenerateArea.second) };
	glm::vec4 particleColor{ 1.f };
	glm::vec3 defaultSpeed{ 0.f };
	m_particles.push_back(Particle{
		generatePosition,
		{ },
		particleColor,
		{ },
		m_particlesLifeTime
	});
}

void ParticleSystem::ParticleUpdate(Particle& particle) {
	particle.lifeTime -= m_deltaTime;
	particle.speed.y -= gravity * m_deltaTime;

	particle.position += particle.speed * m_deltaTime;
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
	glBufferData(GL_ARRAY_BUFFER, m_particles.size() * sizeof(Particle), &m_particles[0], GL_DYNAMIC_DRAW);

	// location 0번에 Particle객체의 position정보를 넘겨줌
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, position));
	glEnableVertexAttribArray(0);

	// location 1번에 Particle객체의 texture정보를 넘겨줌
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, texture));
	glEnableVertexAttribArray(1);

	// location 2번에 Particle객체의 color정보를 넘겨줌
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, color));
	glEnableVertexAttribArray(2);

	glPatchParameteri(GL_PATCH_VERTICES, 3);
}

void ParticleSystem::Update(float deltaTime) {
	if (m_timeElapsed > m_newParticleCreateTime) {
		m_timeElapsed = 0.f;
		CreateNewParticle();
	}

	for (auto& particle : m_particles) {
		ParticleUpdate(particle);
	}

	RemoveLifeEndParticles();

	SetParticleVertexs();
}

void ParticleSystem::Render() {
	glBindVertexArray(m_particleVAO);
	glDrawArrays(m_particleDrawMode, 0, m_particles.size());
	glBindVertexArray(0);
}
