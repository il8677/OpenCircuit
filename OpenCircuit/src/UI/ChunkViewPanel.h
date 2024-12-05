#include <SFML/Graphics.hpp>

#include <imgui.h>

class Chunk;

class ChunkViewPanel {
public:
	ChunkViewPanel(Chunk& chunk) : m_chunk(chunk) {}

	void render();
private:
	Chunk& m_chunk;

	ImVec2 m_viewportSize;
	sf::RenderTexture m_texture;
};