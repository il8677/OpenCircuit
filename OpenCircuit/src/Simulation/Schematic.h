#pragma once
#include "Chunk.h"
#include <string>
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

