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
		Component::components.push_back(new Junction());
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

bool Junction::update(vec4<bool> neighbours, DIR sourceDir) {
	//if dir is divisible by 2 it means its up / down (0 and 2 respectivley)
	bool& utarget = (sourceDir % 2 == 0) ? _udState : _state;
	bool old = utarget;
	utarget = neighbours.values[sourceDir];

	return !(old == utarget);
}


bool Junction::getState(DIR sourceDir) {

	return (sourceDir % 2 == 0) ? _udState : _state;
}