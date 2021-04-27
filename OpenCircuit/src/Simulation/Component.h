#pragma once
#include "../Utility/vec4.h"

#include <vector>

//0 = nothing
//1 = wire
//2 = input
//3 = outputs
//4 = transistor
//5 = Not
//6 = Junction

#define COMPONENTDEF(identifier, name) public: virtual int id() override{return identifier;} virtual Component* copy() override{return new name(*this);}

class Component
{
public:
	virtual int id() { return 0;}
	virtual Component* copy() { return new Component(); }

	// Returns what the updated state would be after a change from  the specified direction
	virtual char predictState(vec4<bool> neighbours, DIR sourceDir, char state) const;

	virtual bool getOutput(DIR direction, char state);

	static std::vector<Component*> components;
	static void initializeComponenets();
};

class Wire : public Component {
	COMPONENTDEF(1, Wire)
	char predictState(vec4<bool> neighbours, DIR sourceDir, char state) const override;
public:
};

class Input : public Component {
	COMPONENTDEF(2, Input)
	char predictState(vec4<bool> neighbours, DIR sourceDir, char state) const override;
};

class Output : public Wire {
	COMPONENTDEF(3, Output)
public:
};

class Transistor : public Component {
	COMPONENTDEF(4, Transistor)
	char predictState(vec4<bool> neighbours, DIR sourceDir, char state) const override;
};

class Not : public Component {
	COMPONENTDEF(5, Not)
public:
	char predictState(vec4<bool> neighbours, DIR sourceDir, char state) const override;
	bool getOutput(DIR direction, char state) override;
	bool not;
};

class Junction : public Component {
	COMPONENTDEF(6, Junction);
public:
	char predictState(vec4<bool> neighbours, DIR sourceDir, char state) const override;

	bool getOutput(DIR direction, char state) override;
};

class Constant : public Component {
	COMPONENTDEF(7, Constant);
};

class WireInput : public Wire {
	COMPONENTDEF(8, WireInput);

};

class Schematic;
class SubcircuitProxy : public Component {
public:
	Schematic& s;

//TODO: Implement this better
	std::vector<int> inx;
	std::vector<int> iny;

	std::vector<int> outx;
	std::vector<int> outy;

	virtual int id() override { return 999; }
	virtual Component* copy() override {
		throw 1;
	}

	int getSizeX();
	int getSizeY();

	SubcircuitProxy(Schematic&);
};