#include "pch.h"
#include "UI.h"
#include <Util/Engine.h>
#include <Graphics/Shader.h>
#include <Graphics/GraphicBuffers.h>
#include <Util/TextureComponent.h>

UI::UI() {
	m_scale = { 1.f / engine->GetWindowWidthF(), 1.f / engine->GetWindowHeightF(), 0.f };

	float uiDefaultSize = 100.f;
	auto w = uiDefaultSize;
	auto h = uiDefaultSize;

	m_quad = {
		Vertex{ glm::vec3{ -w, h, 0.f }, glm::vec2{ 0.f, 0.f }, { } },
		Vertex{ glm::vec3{ -w, -h, 0.f }, glm::vec2{ 0.f, 1.f }, { } },
		Vertex{ glm::vec3{ w, h, 0.f }, glm::vec2{ 1.f, 0.f }, { } },
		Vertex{ glm::vec3{ w, -h, 0.f }, glm::vec2{ 1.f, 1.f }, { } }
	};

	UISHADER->UseProgram();
	m_buffers = std::make_unique<GraphicBuffers>();
	m_buffers->Init();
	m_buffers->SetVerticies(m_quad);

	m_texture = std::make_unique<TextureComponent>();
	m_texture->LoadTexture("./textures/test_ui0.jpg", false);
	UISHADER->UnUseProgram();
}

UI::~UI() { }

void UI::SetScreenPosition(const glm::vec3& position) {
	m_screenPosition.x = position.x / (engine->GetWindowWidthF() / 2.f);
	m_screenPosition.y = position.y / (engine->GetWindowHeightF() / 2.f);
	m_screenPosition.z = 0.f;
}

void UI::ResizedWindow() {
	m_scale = { 1.f / engine->GetWindowWidthF(), 1.f / engine->GetWindowHeightF(), 0.f };
}

void UI::Render() {
	UISHADER->SetUniformInt("uiImage", 0);
	m_texture->BindingTextures();

	glm::mat4 transform{ 1.f };
	auto scale = glm::scale(transform, m_scale);
	auto translate = glm::translate(transform, m_screenPosition);
	transform = translate * scale;
	UISHADER->SetUniformMat4("transform", transform);

	UISHADER->UseProgram();
	m_buffers->SetDrawMode(GL_TRIANGLE_STRIP);
	m_buffers->Render();
	UISHADER->UnUseProgram();
}

Reticle::Reticle() {
	m_scale = { 1.f / engine->GetWindowWidthF(), 1.f / engine->GetWindowHeightF(), 0.f };

	float uiDefaultSize = 30.f;
	float offSet = 3.f;
	auto w = uiDefaultSize;
	auto h = uiDefaultSize;

	m_quad = {
		Vertex{ glm::vec3{ -w, 0.f, 0.f }, glm::vec2{ 0.f, 1.f }, { } },
		Vertex{ glm::vec3{ -offSet, 0.f, 0.f }, glm::vec2{ 1.f, 1.f }, { } },
		Vertex{ glm::vec3{ offSet, 0.f, 0.f }, glm::vec2{ 1.f, 0.f }, { } },
		Vertex{ glm::vec3{ w, 0.f, 0.f }, glm::vec2{ 0.f, 0.f }, { } },
		Vertex{ glm::vec3{ 0.f, -h, 0.f }, glm::vec2{ 1.f, 1.f }, { } },
		Vertex{ glm::vec3{ 0.f, -offSet, 0.f }, glm::vec2{ 1.f, 1.f }, { } },
		Vertex{ glm::vec3{ 0.f, offSet, 0.f }, glm::vec2{ 1.f, 1.f }, { } },
		Vertex{ glm::vec3{ 0.f, h, 0.f }, glm::vec2{ 1.f, 1.f }, { } },
	};

	UISHADER->UseProgram();
	m_buffers = std::make_unique<GraphicBuffers>();
	m_buffers->Init();
	m_buffers->SetVerticies(m_quad);

	UISHADER->UnUseProgram();
}

Reticle::~Reticle() { }

void Reticle::ResizedWindow() {
	m_scale = { 1.f / engine->GetWindowWidthF(), 1.f / engine->GetWindowHeightF(), 0.f };
}

void Reticle::Render() {
	glm::mat4 transform{ 1.f };
	transform = glm::scale(transform, m_scale);
	UISHADER->SetUniformMat4("transform", transform);

	UISHADER->UseProgram();
	m_buffers->SetDrawMode(GL_LINES);
	m_buffers->Render();
	UISHADER->UnUseProgram();
}
