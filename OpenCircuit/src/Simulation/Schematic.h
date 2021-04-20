#pragma once
#include <string>
#include "Chunk.h"

class Schematic
{
	Chunk chunk;
	std::string name;
public:
	Schematic(std::string name);
	Schematic(std::string name, Chunk c);

	std::string getName();
	Chunk* getChunk();

	void clearChunk();
	void setChunk(Chunk c);
};

