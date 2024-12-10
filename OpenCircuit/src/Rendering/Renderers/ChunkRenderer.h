#pragma once
#include "../../Utility/vec4.h"
#include "../Window/SFMLWindow.h"
#include <tuple>

#define VERTDIST 31

class Chunk;

class ChunkRenderer {
	static sf::VertexArray cells;
	static sf::VertexArray grid;

	static std::tuple<int, int, int, int>  getChunkBounds(Chunk& c);

public:

	static vec4<unsigned char> getComponentColour(int componenetId);

	static void Render(sf::RenderTarget& w, Chunk* c, bool doClip=false);
	static void worldToGrid(int& x, int& y); // TODO: Move this to a better place
	static void worldToGridClip(int& x, int& y, Chunk& c);
};
