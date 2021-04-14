#pragma once
#include "../Utility/vec4.h"

//0 = nothing
//1 = wire
//2 = input
//3 = outputs
//4 = transistor
//5 = ntransistor

#define COMPONENTDEF(identifier) public: static const int id = identifier

class Component
{
	COMPONENTDEF(0);
protected:
	bool state;

	// Returns what the updated state would be after a change from  the specified direction
	virtual bool predictOutput(vec4<bool> neighbours, DIR sourceDir) const;
public:

	// Updates the component state after a change from the specified direction
	// Returns if value was changed
	bool update(vec4<bool> neighbours, DIR updatedDirection);

	bool getState();
	void setState(bool s);
};

class Wire : public Component {
	COMPONENTDEF(1);
protected:
	bool predictOutput(vec4<bool> neighbours, DIR sourceDir) const override;
public:
};

class Input : public Component {
	COMPONENTDEF(2);
protected:
	bool predictOutput(vec4<bool> neighbours, DIR sourceDir) const override;
public:
};

class Output : public Wire {
	COMPONENTDEF(3);
public:
};

class Transistor : public Component {
	COMPONENTDEF(4);
public:	
	bool predictOutput(vec4<bool> neighbours, DIR sourceDir) const override;
};

class nTransistor : public Transistor {
	COMPONENTDEF(5);
public:
	bool predictOutput(vec4<bool> neighbours, DIR sourceDir) const override;
};

