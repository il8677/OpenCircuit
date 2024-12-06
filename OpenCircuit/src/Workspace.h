#pragma once
#include <vector>
#include <string>
#include <memory>

#include "Simulation/Schematic.h"
#include "Simulation/Chunk.h"

class Workspace
{
	std::vector<Schematic*> schematics;
	
	Chunk workingChunk;
	int workingChunkId;
public:
	Workspace();

	Schematic* getSchematic(int i);

	Schematic* getSchematic();

	Chunk* getChunk();

	void deleteSchematic(int i);

	void setWorkingSchematic(int i);

	int schematicCount();
	int getWorkingChunk();

	void moveUp(int i);

	void newSchematic(std::string name);

	void save(std::ofstream&);
	void load(std::ifstream&);
};