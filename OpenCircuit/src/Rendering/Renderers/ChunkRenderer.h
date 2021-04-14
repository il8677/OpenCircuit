#pragma once
#include "../Window/window.h"

// TODO: Abstract and decouple from SFML

class Chunk;

class ChunkRenderer {
	Chunk& c;

public:

	ChunkRenderer(Chunk& c);

	void Render(Window& w);
};