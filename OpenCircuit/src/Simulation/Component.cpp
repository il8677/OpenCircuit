#include "Component.h"

//TODO: Split implementations into seperate files
bool Component::getState() {
	return state;
}

void Component::setState(bool s) {
	state = s;
}

bool Component::predictOutput(vec4<bool> neighbours, DIR sourceDir) const{
	return false;
}

bool Component::update(vec4<bool> neighbours, DIR sourceDir) {
	bool oldState = state;
	state = predictOutput(neighbours, sourceDir);
	return !oldState == state;
}

bool Wire::predictOutput(vec4<bool> neighbours, DIR sourceDir) const{
	return neighbours.values[sourceDir];
}

bool Input::predictOutput(vec4<bool> neighbours, DIR sourceDir) const{
	return state;
}

bool Transistor::predictOutput(vec4<bool> neighbours, DIR sourceDir) const {
	return neighbours.up && neighbours.left;
}

bool nTransistor::predictOutput(vec4<bool> neighbours, DIR sourceDir) const{
	return !Transistor::predictOutput(neighbours, sourceDir);
}