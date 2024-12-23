#pragma once
#include "../Utility/vec4.h"

#include <vector>

enum ComponentType {
	NOCOMPONENT=0,
	WIRE,
	INPUT,
	OUTPUT,
	TRANSISTOR,
	NOT,
	JUNCTION,
	CONSTANT,
	WIRE_INPUT,

	SUBCIRCUIT_PROXY=999
};

#define COMPONENTDEF(identifier, name) \
	public: \
		virtual ComponentType id() override{return identifier;} \
		virtual Component* copy() override{return new name();}

class Component
{
public:
	virtual ComponentType id() { return NOCOMPONENT;}
	virtual Component* copy() { return new Component(); }

	// Returns what the updated state would be after a change from  the specified direction
	virtual char predictState(vec4<bool> neighbours, DIR sourceDir, char state) const;

	virtual bool getOutput(DIR direction, char state);

	static std::vector<Component*> components;
	static void initializeComponenets();
	static Component* getComponentOfId(int id);
};

class Wire : public Component {
	COMPONENTDEF(WIRE, Wire)
	char predictState(vec4<bool> neighbours, DIR sourceDir, char state) const override;
	bool getOutput(DIR direction, char state) override;
};

class Input : public Component {
	COMPONENTDEF(INPUT, Input)
	char predictState(vec4<bool> neighbours, DIR sourceDir, char state) const override;
};

class Output : public Wire {
	COMPONENTDEF(OUTPUT, Output)
public:
};

class Transistor : public Component {
	COMPONENTDEF(TRANSISTOR, Transistor)
	char predictState(vec4<bool> neighbours, DIR sourceDir, char state) const override;
	bool getOutput(DIR direction, char state) override;
};

class Not : public Component {
	COMPONENTDEF(NOT, Not)
public:
	char predictState(vec4<bool> neighbours, DIR sourceDir, char state) const override;
	bool getOutput(DIR direction, char state) override;
};

class Junction : public Wire {
	COMPONENTDEF(JUNCTION, Junction);
public:
	bool getOutput(DIR direction, char state) override;
};

class Constant : public Component {
	COMPONENTDEF(CONSTANT, Constant);
};

class WireInput : public Wire {
	COMPONENTDEF(WIRE, WireInput);

};

class Schematic;
class SubcircuitProxy : public Component {
public:
	Schematic* s;

//TODO: Implement this better
	std::vector<int> inx;
	std::vector<int> iny;

	std::vector<int> outx;
	std::vector<int> outy;

	virtual ComponentType id() override { return SUBCIRCUIT_PROXY; }
	Component* copy() override {
		return nullptr;
	};

	int getSizeX();
	int getSizeY();

	SubcircuitProxy(Schematic*);
};
