#include "Component.h"

//TODO: Split implementations into seperate files
bool Component::getState() {
	return _state;
}

void Component::setState(bool s) {
	_state = s;
}

bool Component::predictOutput(vec4<bool> neighbours, DIR sourceDir) const{
	return false;
}

bool Component::update(vec4<bool> neighbours, DIR sourceDir) {
	bool oldState = _state;
	_state = predictOutput(neighbours, sourceDir);
	return !oldState == _state;
}

bool Wire::predictOutput(vec4<bool> neighbours, DIR sourceDir) const{
	return neighbours.values[sourceDir];
}

bool Input::predictOutput(vec4<bool> neighbours, DIR sourceDir) const{
	return _state;
}

bool Transistor::predictOutput(vec4<bool> neighbours, DIR sourceDir) const {
	return neighbours.up && neighbours.left;
}

bool nTransistor::predictOutput(vec4<bool> neighbours, DIR sourceDir) const{
	return !Transistor::predictOutput(neighbours, sourceDir);
}