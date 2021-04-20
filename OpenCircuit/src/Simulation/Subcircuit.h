#pragma once
#include "Component.h"
#include "Schematic.h"

#include <memory>
#include <vector>

class Subcircuit : Component
{
	Schematic containedCircuit;
	//Pointer to the array location of the heap allocated memory location, this way it still works if the component is overwritten by user
	std::vector<Component**> inputs;
	std::vector<Component**> outputs;

public: 
	virtual int id() override { return 999; } 
	virtual Component* copy() override {
		throw 1;
	}

	void addInput(Component** inp);
	void addOutput(Component** out);

	Subcircuit(Schematic& containedChunk);
	
	int outputPinsCount();
	int inputPinsCount();

	int getSizeX();
	int getSizeY();
	void tick();

	void setSchematic(Schematic& s);
	Schematic& getSchematic();

	std::string getName();

	bool update(vec4<bool> neighbours, DIR sourceDir) override;
	bool getState(DIR direction) override;
};

