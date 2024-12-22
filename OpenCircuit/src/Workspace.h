#pragma once
#include <vector>
#include <string>
#include <memory>

#include "Simulation/Schematic.h"
#include "Simulation/Chunk.h"

class Workspace
{
	std::vector<Schematic*> schematics;
public:
	std::string notes;

	Workspace();

	Schematic* getSchematic(int i);
	Schematic* getSchematic();

	void deleteSchematic(int i);

	int schematicCount();

	void moveUp(int i);

	void newSchematic(std::string name);

	void save(std::ofstream&);
	void load(std::ifstream&);
};