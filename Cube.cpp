#include "pch.h"
#include "Cube.h"
#include "Graphics/Shader.h"
#include "Model/Model.h"
#include "Model/ModelList.h"

Cube::Cube() {
	m_model = MODELLIST->GetModel(m_modelTag);
	m_model->SetObjectColor(glm::vec3{ 1.f, 0.f, 0.f });
}

Cube::~Cube() { }

void Cube::Update(float deltaTime) {
}

void Cube::Render() {
	Object::Render();
}
