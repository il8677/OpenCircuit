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
bool Component::getOutput(DIR direction, char state) {
	return state;
}

char Component::predictState(vec4<bool> neighbours, DIR sourceDir, char state, std::array<bool, 4>& doUpdate) const{
	return 0;
}

char Wire::predictState(vec4<bool> neighbours, DIR sourceDir, char state, std::array<bool, 4>& doUpdate) const{
	char newState = neighbours.values[sourceDir];

	if (newState != state) doUpdate = { true, true, true, true };

	return newState;
}

char Transistor::predictState(vec4<bool> neighbours, DIR sourceDir, char state, std::array<bool, 4>& doUpdate) const {
	char newState = neighbours.up && neighbours.left;

	if (newState != state) {
		doUpdate = {false, true, false, false};
	}

	return newState;
}

bool Transistor::getOutput(DIR direction, char state)
{
	if (direction == RIGHT) {
		return state;
	}

	return false;
}

char Not::predictState(vec4<bool> neighbours, DIR sourceDir, char state, std::array<bool, 4>& doUpdate) const{

	char newState = !neighbours.left;

	if (newState != state) {
		doUpdate = { false, true, false, false };
	}

	return newState;
}

bool Not::getOutput(DIR direction, char state)
{
	if (direction == LEFT) {
	}
	return state;
}

char Junction::predictState(vec4<bool> neighbours, DIR sourceDir, char state, std::array<bool, 4>& doUpdate) const {
	//Bit 1 of state stores u/d, bit 2 stores l/r
	//This returns which bit we're meant to be using, if we want to toggle bit 1 it returns 01, otherwise, it returns 10
	//conveluted, but it works
	char mask = (sourceDir % 2 == 0 ? 1 : 2);
	char others = state & ~mask; // Everything except what we want masked
	char newState = others | ((neighbours.values[sourceDir]) << (mask - 1));
	
	//Maximum 1 change, 1 if u/d (0, 2) , 2 if l/r (3, 1)
	char difference = newState ^ state;

	if (difference) {
		doUpdate[difference-1] = true;
		doUpdate[difference+1] = true;
	}

	return newState;
}

bool Junction::getOutput(DIR sourceDir, char state) {
	if (sourceDir == NONE) {
		return state;
	}

	char mask = (sourceDir % 2 == 0 ? 1 : 2);

	return (state & mask);
}

char Input::predictState(vec4<bool> neighbours, DIR sourceDir, char state, std::array<bool, 4>& doUpdate) const
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

