#pragma once
#include "../../Utility/vec4.h"
#include "../Window/SFMLWindow.h"


class SFMLWindow;
class Chunk;

// TODO: Abstract and decouple from SFML


class ChunkRenderer {
	static sf::VertexArray cells;
	static sf::VertexArray grid;

public:

	static vec4<unsigned char> getComponentColour(int componenetId);

	static void Render(SFMLWindow& w, Chunk* c);
	static void worldToGrid(int& x, int& y); // TODO: Move this to a better place
};
