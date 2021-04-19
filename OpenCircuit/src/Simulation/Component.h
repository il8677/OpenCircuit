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

protected:
	bool _state;

	// Returns what the updated state would be after a change from  the specified direction
	virtual bool predictOutput(vec4<bool> neighbours, DIR sourceDir) const;
public:

	// Updates the component state after a change from the specified direction
	// Returns if value was changed
	virtual bool update(vec4<bool> neighbours, DIR updatedDirection);

	//Returns the state for the given direction
	virtual bool getState(DIR direction);
	virtual void setState(bool s);

	static std::vector<Component*> components;
	static void initializeComponenets();
};

class Wire : public Component {
	COMPONENTDEF(1, Wire)
protected:
	bool predictOutput(vec4<bool> neighbours, DIR sourceDir) const override;
public:
};

class Input : public Component {
	COMPONENTDEF(2, Input)
protected:
	bool predictOutput(vec4<bool> neighbours, DIR sourceDir) const override;
public:
	bool* getStatePointer();
};

class Output : public Wire {
	COMPONENTDEF(3, Output)
public:
};

class Transistor : public Component {
	COMPONENTDEF(4, Transistor)
public:	
	bool predictOutput(vec4<bool> neighbours, DIR sourceDir) const override;
};

class Not : public Component {
	COMPONENTDEF(5, Not)
public:

	bool getState(DIR direction) override;

	bool predictOutput(vec4<bool> neighbours, DIR sourceDir) const override;
};

class Junction : public Component {
	COMPONENTDEF(6, Junction);
protected:
	bool _udState; // State for the up down track _state is used for l/r state
public:
	bool getState(DIR direction) override;
	bool update(vec4<bool> neighbours, DIR sourceDir) override;
	
	void setState(bool s) override;
};