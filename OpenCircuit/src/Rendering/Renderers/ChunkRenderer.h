#pragma once
#include "../Window/window.h"

// TODO: Abstract and decouple from SFML

class Chunk;

static class ChunkRenderer {

public:

	static void Render(Window& w, Chunk& c);

	static void worldToGrid(int& x, int& y); // TODO: Move this to a better place
};