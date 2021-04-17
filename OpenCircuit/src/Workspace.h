#pragma once
#include <vector>
#include <string>
#include <memory>

#include "Simulation/Schematic.h"
#include "Simulation/Chunk.h"

class Workspace
{
	std::vector<Schematic> schematics;
	
	Schematic* workingSchematic;
public:
	Workspace();

	Schematic* getSchematic(int i);
	Schematic* getSchematic();

	void setWorkingSchematic(int i);

	int schematicCount();

	void newSchematic(std::string name);

	void paint(int gridx, int gridy, int id);
};