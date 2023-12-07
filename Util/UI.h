#pragma once

class UI {
public:
	UI();
	~UI();

private:
	std::vector<class Vertex> m_quad{ };
	std::unique_ptr<class TextureComponent> m_texture{ };
	std::unique_ptr<class GraphicBuffers> m_buffers{ };

public:
	
};