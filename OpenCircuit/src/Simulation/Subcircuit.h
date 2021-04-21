#pragma once
#include "Component.h"
#include "Chunk.h"
#include <memory>
#include <vector>

class Subcircuit
{
	Chunk containedCircuit;
	//Pointer to the array location of the heap allocated memory location, this way it still works if the component is overwritten by user
	std::vector<char*> inputs;
	std::vector<char*> outputs;

public: 

	void addInput(char* inp);
	void addOutput(char* out);


	void tick();

	void setSchematic(Schematic& s);
	Schematic& getSchematic();

	std::string getName();
	
	Subcircuit(const Chunk& containedChunk);
	Subcircuit(Schematic& containedSchematic);
};

