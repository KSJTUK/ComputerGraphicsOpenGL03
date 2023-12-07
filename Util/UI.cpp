#include "pch.h"
#include "UI.h"
#include <Graphics/GraphicBuffers.h>

UI::UI() {
	m_quad = {
		Vertex{ glm::vec3{ -0.1f, 0.1f, 0.f }, glm::vec2{ 0.f, 0.f }, { } },
		Vertex{ glm::vec3{ -0.1f, -0.1f, 0.f }, glm::vec2{ 0.f, 1.f }, { } },
		Vertex{ glm::vec3{ 0.1f, 0.1f, 0.f }, glm::vec2{ 1.f, 0.f }, { } },
		Vertex{ glm::vec3{ 0.1f, -0.1f, 0.f }, glm::vec2{ 1.f, 1.f }, { } }
	};

	m_buffers = std::make_unique<GraphicBuffers>();
	m_buffers->Init();
}

UI::~UI() { }
