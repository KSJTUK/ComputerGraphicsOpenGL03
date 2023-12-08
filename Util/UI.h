#pragma once

class UI {
public:
	UI();
	//UI();
	~UI();

private:
	std::vector<Vertex> m_quad{ };
	std::unique_ptr<class TextureComponent> m_texture{ };
	std::unique_ptr<class GraphicBuffers> m_buffers{ };

	glm::vec3 m_screenPosition{ };
	glm::vec3 m_scale{ 1.f };

public:
	void SetScreenPosition(const glm::vec3& position);
	void ResizedWindow();

	void Update(float deltaTime);
	void Render();

};

class Reticle {
public:
	Reticle();
	~Reticle();

private:
	std::vector<Vertex> m_quad{ };
	std::unique_ptr<class GraphicBuffers> m_buffers{ };

	glm::vec3 m_screenPosition{ };
	glm::vec3 m_scale{ 1.f };

public:
	void ResizedWindow();

	void Update(float deltaTime);
	void Render();
};