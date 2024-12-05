#pragma once
#include "../../Utility/vec4.h"
#include "../Window/SFMLWindow.h"


class Chunk;

class ChunkRenderer {
	static sf::VertexArray cells;
	static sf::VertexArray grid;

public:

	static vec4<unsigned char> getComponentColour(int componenetId);

	static void Render(sf::RenderTarget& w, Chunk* c);
	static void worldToGrid(int& x, int& y); // TODO: Move this to a better place
};
