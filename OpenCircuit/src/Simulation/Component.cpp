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

//TODO: Split implementations into seperate files
bool Component::getOutput(DIR direction, char state) {
	return state;
}

char Component::predictState(vec4<bool> neighbours, DIR sourceDir, char state) const{
	return 0;
}

char Wire::predictState(vec4<bool> neighbours, DIR sourceDir, char state) const{
	return neighbours.values[sourceDir];
}

char Transistor::predictState(vec4<bool> neighbours, DIR sourceDir, char state) const {
	return neighbours.up && neighbours.left;
}

char Not::predictState(vec4<bool> neighbours, DIR sourceDir, char state) const{
	return !neighbours.left;
}

char Junction::predictState(vec4<bool> neighbours, DIR sourceDir, char state) const {
	//Bit 1 = u/d, bit 2 = l/r
	char mask = (sourceDir % 2 == 0 ? 1 : 2) & neighbours.values[sourceDir];

	return state & mask;
}

bool Junction::getOutput(DIR sourceDir, char state) {
	//Reversed as we want to mask in
	char mask = (sourceDir % 2 == 0 ? 2 : 1);

	return state & mask;
}

char Input::predictState(vec4<bool> neighbours, DIR sourceDir, char state) const
{
	return state;
}

int SubcircuitProxy::getSizeX() {
	return 3;
}

#include "Schematic.h"

int SubcircuitProxy::getSizeY() {
	int maxPins = s.inputCount() > s.outputCount() ? s.inputCount() : s.outputCount();

	if (maxPins > 2) {
		return 3 + 2 * (maxPins - 2);
	}
	else {
		return 3;
	}
}
SubcircuitProxy::SubcircuitProxy(Schematic& s) : s(s)
{
}
