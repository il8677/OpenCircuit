#pragma once
#include <vector>
#include <string>
#include <memory>

#include "Simulation/Schematic.h"
#include "Simulation/Chunk.h"

class Workspace
{
	std::vector<Schematic> schematics;
	
	Chunk workingChunk;
public:
	Workspace();

	Schematic* getSchematic(int i);

	Schematic* getSchematic();

	Chunk* getChunk();

	void deleteSchematic(int i);

	void setWorkingSchematic(int i);

	int schematicCount();

	void newSchematic(std::string name);

	void placeSubcircuit(int x, int y, int cid);

	void paint(int gridx, int gridy, int id);
};