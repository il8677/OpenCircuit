#include "Component.h"

#include "Schematic.h"

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

char Component::predictState(vec4<bool> neighbours, DIR sourceDir, char state) const{
	return 0;
}

char Wire::predictState(vec4<bool> neighbours, DIR sourceDir, char state) const{
	char targetBit = 1 << sourceDir;
	char setTo = neighbours.values[sourceDir] << sourceDir;

	return state & ~targetBit | setTo;
}

bool Wire::getOutput(DIR direction, char state) {
	char targetBit = 1 << direction;
	return state & ~targetBit;
}

char Transistor::predictState(vec4<bool> neighbours, DIR sourceDir, char state) const {
	return neighbours.up && neighbours.left;
}

char Not::predictState(vec4<bool> neighbours, DIR sourceDir, char state) const{
	return !neighbours.left;
}

bool Not::getOutput(DIR direction, char state)
{
	if (direction == RIGHT) {
		return state;
	}
	return !state;
}

bool Junction::getOutput(DIR sourceDir, char state) {
	if (sourceDir == NONE)
		return state;
	else if (sourceDir == UP) sourceDir = DOWN;
	else if (sourceDir == LEFT) sourceDir = RIGHT;
	else if (sourceDir == DOWN) sourceDir = UP;
	else if (sourceDir == RIGHT) sourceDir = LEFT;

	char targetBit = 1 << sourceDir;
	return state & targetBit;
}

char Input::predictState(vec4<bool> neighbours, DIR sourceDir, char state) const
{
	return state;
}

int SubcircuitProxy::getSizeX() {
	return s->inputCount() >= 3 ? 3 : 1;
}

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

