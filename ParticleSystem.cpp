#include "pch.h"
#include "ParticleSystem.h"
#include "Graphics/Shader.h"

ParticleSystem::ParticleSystem() { 
	PARTICLESHADER->UseProgram();
	glPointSize(m_primitiveSize);
	glGenVertexArrays(1, &m_particleVAO);
	glGenBuffers(1, &m_particleVBO);

	glBindVertexArray(m_particleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_particleVBO);
	PARTICLESHADER->UnUseProgram();
}

ParticleSystem::ParticleSystem(float lifeTime, int maxCountParticles) 
	: m_particlesLifeTime{ lifeTime }, m_maxCountParticle{ maxCountParticles } {
	PARTICLESHADER->UseProgram();
	glPointSize(m_primitiveSize);
	glGenVertexArrays(1, &m_particleVAO);
	glGenBuffers(1, &m_particleVBO);

	glBindVertexArray(m_particleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_particleVBO);
	PARTICLESHADER->UnUseProgram();
}

ParticleSystem::ParticleSystem(float lifeTime, int maxCountParticles, float createTime) 
	:m_particlesLifeTime{ lifeTime }, m_maxCountParticle{ maxCountParticles }, m_newParticleCreateTime{ createTime } {
	PARTICLESHADER->UseProgram();
	glPointSize(m_primitiveSize);
	glGenVertexArrays(1, &m_particleVAO);
	glGenBuffers(1, &m_particleVBO);

	glBindVertexArray(m_particleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_particleVBO);
	PARTICLESHADER->UnUseProgram();
}

ParticleSystem::ParticleSystem(std::pair<glm::vec3, glm::vec3>& generateParticleArea, float lifeTime, int maxCountParticles, float createTime) 
	: m_particleGenerateArea{ generateParticleArea }, m_particlesLifeTime {lifeTime },
	m_maxCountParticle{ maxCountParticles }, m_newParticleCreateTime{ createTime } {
	PARTICLESHADER->UseProgram();
	glPointSize(m_primitiveSize);
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
	m_particles.push_back(Particle{
		generatePosition,
		{ },
		particleColor,
		defaultSpeed,
		m_particlesLifeTime
	});
}

void ParticleSystem::ParticleUpdate(Particle& particle) {
	particle.lifeTime -= m_deltaTime;

	if (particle.speed.y > -endGravitySpeed) {
		particle.speed.y -= gravity * m_deltaTime;
	}

	particle.position += particle.speed * m_deltaTime;
	if (particle.position.y < -2.5f) {
		particle.position.y = -2.5f;
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
	PARTICLESHADER->UseProgram();

	glBindVertexArray(m_particleVAO);

	glBufferData(GL_ARRAY_BUFFER, m_particles.size() * sizeof(Particle), &m_particles[0], GL_DYNAMIC_DRAW);

	// location 0번에 Particle객체의 position정보를 넘겨줌
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, position));
	glEnableVertexAttribArray(0);

	// location 1번에 Particle객체의 texture정보를 넘겨줌
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, texture));
	glEnableVertexAttribArray(1);

	// location 2번에 Particle객체의 color정보를 넘겨줌
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, color));
	glEnableVertexAttribArray(2);
	PARTICLESHADER->UnUseProgram();
}

void ParticleSystem::SetPerspectiveMatrix(const glm::mat4& perspectiveMatrix) {
	PARTICLESHADER->UseProgram();
	PARTICLESHADER->SetPerspectiveMat(perspectiveMatrix);
	PARTICLESHADER->UnUseProgram();
}

void ParticleSystem::Update(float deltaTime) {
	m_deltaTime = deltaTime;

	if (m_timeElapsed > m_newParticleCreateTime) {
		m_timeElapsed = 0.f;
		CreateNewParticle();
	}

	for (auto& particle : m_particles) {
		ParticleUpdate(particle);
	}
	std::cout << "particles count: " << m_particles.size() << std::endl;

	RemoveLifeEndParticles();

	if (!m_particles.empty()) {
		SetParticleVertexs();
	}
	m_timeElapsed += deltaTime;
}

void ParticleSystem::Render() {
	PARTICLESHADER->UseProgram();
	glBindVertexArray(m_particleVAO);
	glDrawArrays(m_particleDrawMode, 0, uint32(m_particles.size()));
	glBindVertexArray(0);
	PARTICLESHADER->UseProgram();
}
