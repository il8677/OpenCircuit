#pragma once
#include <string>
#include <vector>
#include <forward_list>
#include <fstream>

class Subcircuit;
class Component;
class Input;
class Output;
class SubcircuitProxy;

#define CHUNK_X 32
#define CHUNK_Y 32

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

	void replace(int x, int y, Component* with);

	void placeSubcircuit(int x, int y, Schematic& s);
	void deleteSubcircuit(SubcircuitProxy* s);
	void deleteSubcircuit(int x, int y);

	std::vector<Input*>  getInputs() const;
	std::vector<Output*> getOutputs() const;

	int inputCount();
	int outputCount();

	std::string getName();

	Schematic(std::string name);
	~Schematic();

	//Copy constructor, peforms deep copy creating new objects
	Schematic(const Schematic&);

	//Move constructor, takes ownership of all heap allocated objects
	Schematic(Schematic&&) noexcept;

	Schematic& operator=(const Schematic&);
	Schematic& operator=(Schematic&&);

	void save(std::ofstream& fs);
	void load(std::istringstream& is, std::vector<Schematic*>& schematics);
};

