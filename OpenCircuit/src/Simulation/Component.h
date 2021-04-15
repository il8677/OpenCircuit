#pragma once
#include "../Utility/vec4.h"

#include <vector>

//0 = nothing
//1 = wire
//2 = input
//3 = outputs
//4 = transistor
//5 = ntransistor

#define COMPONENTDEF(identifier, name) public: virtual int id() override{return identifier;} virtual Component* copy() override{return new name();}

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
	bool update(vec4<bool> neighbours, DIR updatedDirection);

	bool getState();
	void setState(bool s);

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

class nTransistor : public Transistor {
	COMPONENTDEF(5, nTransistor)
public:
	bool predictOutput(vec4<bool> neighbours, DIR sourceDir) const override;
};