#include "Schematic.h"

Schematic::Schematic(std::string name) : name(name)
{
}

Schematic::Schematic(std::string name, Chunk c) : name(name), chunk(c)
{
}

std::string Schematic::getName() {
	return name;
}

Chunk* Schematic::getChunk()
{
	return &chunk;
}

void Schematic::clearChunk()
{
	chunk.clear();
}

void Schematic::setChunk(Chunk c)
{
	chunk = c;
}
