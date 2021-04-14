#include "Component.h"

//TODO: Split implementations into seperate files
bool Component::getState() {
	return _state;
}

void Component::setState(bool s) {
	_state = s;
}

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
		Component::components.push_back(new nTransistor());
	}

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