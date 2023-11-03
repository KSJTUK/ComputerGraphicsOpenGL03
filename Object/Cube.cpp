#include "pch.h"
#include "Cube.h"
#include "Graphics/Shader.h"
#include "Model/Model.h"
#include "Model/ModelList.h"

Cube::Cube() {
	m_modelTag = "sphere";
	m_model = MODELLIST->GetModel(m_modelTag);
	m_objectColor = glm::vec3{ 1.f, 0.3f, 0.31f };
	m_scaleFactor = glm::vec3{ 0.3f, 0.3f, 0.3f };
}

Cube::~Cube() { }

void Cube::Update(float deltaTime) {
}

void Cube::Render() {
	Object::Render();
}
