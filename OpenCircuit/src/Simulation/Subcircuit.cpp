#include "Subcircuit.h"

void Subcircuit::addInput(Component** inp)
{
	inputs.push_back(inp);
}

void Subcircuit::addOutput(Component** out)
{
	outputs.push_back(out);
}

Subcircuit::Subcircuit(Schematic& containedChunk) : containedCircuit(containedChunk) {
	containedCircuit.getChunk()->reset();
}

void Subcircuit::tick() {
	containedCircuit.getChunk()->tick();

	auto circuitOutputs = containedCircuit.getChunk()->getOutputs();
	for (int i = 0; i < outputPinsCount(); i++) {
		(*outputs[i])->setState(circuitOutputs[i]->getState(NONE));
	}
}

void Subcircuit::setSchematic(Schematic& s)
{
	containedCircuit = s;
}

Schematic& Subcircuit::getSchematic()
{
	return containedCircuit;
}

std::string Subcircuit::getName()
{
	return containedCircuit.getName();
}

bool Subcircuit::update(vec4<bool> neighbours, DIR sourceDir)
{
	auto circuitInputs = containedCircuit.getChunk()->getInputs();
	for (int i = 0; i < inputPinsCount(); i++) {
		circuitInputs[i]->setState((*inputs[i])->getState(NONE));
	}

	containedCircuit.getChunk()->updateInputs();

	return false;
}

bool Subcircuit::getState(DIR direction)
{
	return true;
}

int Subcircuit::outputPinsCount() {
	return containedCircuit.getChunk()->getOutputs().size();
}

int Subcircuit::inputPinsCount() {
	return containedCircuit.getChunk()->getInputs().size();
}

int Subcircuit::getSizeX(){
	return 3;
}

int Subcircuit::getSizeY(){
	int maxPins = inputPinsCount() > outputPinsCount() ? inputPinsCount() : outputPinsCount();

	if (maxPins > 2) {
		return 3 + 2 * (maxPins - 2);
	}
	else {
		return 3;
	}
}