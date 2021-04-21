#pragma once
#include <string>
#include <vector>
#include <forward_list>

class Subcircuit;
class Component;
class Input;
class Output;
class SubcircuitProxy;

#define CHUNK_X 10
#define CHUNK_Y 10

class Schematic
{
	Component* cMap[CHUNK_X][CHUNK_Y];

	std::string name;
public:
	std::forward_list<SubcircuitProxy*> subcircuits;

	int getCellId(int x, int y) const;

	void setComponent(Component* c, int x, int y);
	void setComponent(int cid, int x, int y);

	Component* getComponent(int, int);

	void placeSubcircuit(int x, int y, Schematic& s);

	std::vector<Input*>  getInputs() const;
	std::vector<Output*> getOutputs() const;

	int inputCount();
	int outputCount();

	std::string getName();

	Schematic(std::string name);
	~Schematic();

	//Copy constructor, peforms deep copy creating new objects, shouldn't really ever be used but hey, its here
	Schematic(const Schematic&);
};

