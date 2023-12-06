#include "pch.h"
#include "Object/Object.h"
#include "Graphics/Shader.h"
#include "Model/Model.h"
#include "Model/ModelList.h"
#include "Graphics/Terrain.h"

Object::Object() { }

Object::Object(const std::string& modelTag) : m_modelTag{ modelTag } {
	m_model = MODELLIST->GetModel(modelTag);
}

Object::Object(const std::string& modelTag, const glm::vec4& objectColor) : m_modelTag{ modelTag }, m_objectColor{ objectColor } {
	m_model = MODELLIST->GetModel(modelTag);
}

Object::~Object() { }

void Object::SetMeterials() {
	OBJECTSHADER->SetUniformVec4("objectColor", m_objectColor);
	OBJECTSHADER->SetUniformInt("meterials.diffuse", 0);
	OBJECTSHADER->SetUniformVec3("meterials.specular", m_meterial.specular);
	OBJECTSHADER->SetUniformFloat("meterials.shininess", m_meterial.shininess);
}

bool Object::ExistTexture() const {
	return m_model->ExistTexture();
}

void Object::SetObjectColor(const glm::vec4& color) {
	m_objectColor = color;
}

void Object::SetScale(const glm::vec3& scaleFactor) {
	m_scaleFactor = scaleFactor;
	m_terrainOffset = m_terrainOffset * m_scaleFactor.y;
}

void Object::TerrainCollision(Terrain& terrain) {
	terrain.MoveHeightPosition(m_position, m_terrainOffset);
}
