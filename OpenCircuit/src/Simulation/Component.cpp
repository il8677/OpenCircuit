#include "Component.h"

//TODO: Split implementations into seperate files
bool Component::getState(DIR direction) {
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
		Component::components.push_back(new Not());
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

bool* Input::getStatePointer()
{
	return &_state;
}

bool Transistor::predictOutput(vec4<bool> neighbours, DIR sourceDir) const {
	return neighbours.up && neighbours.left;
}

bool Not::predictOutput(vec4<bool> neighbours, DIR sourceDir) const{
	return !neighbours.left;
}

bool Not::getState(DIR direction) {
	if (direction == LEFT)
		return !_state;
	
	return _state;
}