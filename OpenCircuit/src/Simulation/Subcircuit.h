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

	std::vector<char> lastInputs;

public: 
	std::queue<char*> updatedCells;

	void addInput(char* inp);
	void addOutput(char* out);

	void reset();
	void tick();

	void setSchematic(Schematic* s);
	Schematic* getSchematic();

    Chunk& getChunk() { return containedCircuit; }

	std::string getName();
	
	Subcircuit(const Chunk& containedChunk);
	Subcircuit(Schematic* containedSchematic);

	Subcircuit(const Subcircuit&)=default;
	Subcircuit(Subcircuit&&)=default;

	Subcircuit& operator=(const Subcircuit&)=default;
	Subcircuit& operator=(Subcircuit&&)=default;
};

