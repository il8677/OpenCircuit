#include "Component.h"


void Component::initializeComponenets()
{
	static bool ran;
	if (!ran) {
		ran = true;

		Component::components.push_back(new Component());
		Component::components.push_back(new Wire());
		Component::components.push_back(new Input());
		Component::components.push_back(new Output());
		Component::components.push_back(new Transistor());
		Component::components.push_back(new Not());
		Component::components.push_back(new Junction());
	}

}

Component* Component::getComponentOfId(int id)
{
	if (0 < id && id < components.size()) {
		return components[id]->copy();
	}
	else {
		return new Component();
	}
}

//TODO: Split implementations into seperate files
BOOLEAN Component::getOutput(DIR direction, char state) {
	return state ? TRUE: FALSE;
}

char Component::predictState(vec4<BOOLEAN> neighbours, DIR sourceDir, char state) const{
	return 0;
}

char Wire::predictState(vec4<BOOLEAN> neighbours, DIR sourceDir, char state) const{
	if (neighbours.values[sourceDir] == DC) {
		return state;
	}

	return neighbours.values[sourceDir];
}

char Transistor::predictState(vec4<BOOLEAN> neighbours, DIR sourceDir, char state) const {
	return neighbours.up && neighbours.left;
}

BOOLEAN Transistor::getOutput(DIR direction, char state)
{
	if (direction == RIGHT) {
		return state ? TRUE : FALSE;
	}

	return DC;
}

char Not::predictState(vec4<BOOLEAN> neighbours, DIR sourceDir, char state) const{
	return neighbours.left == TRUE ? 0 : 1;
}

BOOLEAN Not::getOutput(DIR direction, char state)
{
	if (direction == LEFT) {
		return DC;
	}
	return state ? TRUE : FALSE;
}

char Junction::predictState(vec4<BOOLEAN> neighbours, DIR sourceDir, char state) const {
	//Bit 1 of state stores u/d, bit 2 stores l/r

	//This returns which bit we're meant to be using, if we want to toggle bit 1 it returns 01, otherwise, it returns 10
	//conveluted, but it works
	char mask = (sourceDir % 2 == 0 ? 1 : 2);
	char others = state & ~mask; // Everything except what we want masked

	return others | (neighbours.values[sourceDir]<< (mask-1));
}

BOOLEAN Junction::getOutput(DIR sourceDir, char state) {
	if (sourceDir == NONE) {
		return state ? TRUE : FALSE;
	}

	char mask = (sourceDir % 2 == 0 ? 1 : 2);

	return (state & mask) ? TRUE : FALSE;
}

char Input::predictState(vec4<BOOLEAN> neighbours, DIR sourceDir, char state) const
{
	return state;
}

int SubcircuitProxy::getSizeX() {
	return 3;
}

#include "Schematic.h"

int SubcircuitProxy::getSizeY() {
	int maxPins = s->inputCount() > s->outputCount() ? s->inputCount() : s->outputCount();

	if (maxPins > 2) {
		return 3 + 2 * (maxPins - 2);
	}
	else {
		return 3;
	}
}
SubcircuitProxy::SubcircuitProxy(Schematic* s) : s(s)
{
}

