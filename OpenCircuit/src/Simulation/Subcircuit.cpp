#include "Subcircuit.h"

void Subcircuit::addInput(std::shared_ptr<Wire>& inp)
{
	inputs.push_back(std::weak_ptr<Wire>(inp));
}

void Subcircuit::addOutput(std::shared_ptr<Constant>& out)
{
	outputs.push_back(std::weak_ptr<Constant>(out));
}

Subcircuit::Subcircuit(Chunk& containedChunk) {
	c = containedChunk;
	c.reset();
}

void Subcircuit::tick() {
	c.tick();

	auto circuitOutputs = c.getOutputs();
	for (int i = 0; i < outputPinsCount(); i++) {
		std::shared_ptr<Constant> out = outputs[i].lock();
		out.get()->setState(circuitOutputs[i]->getState(NONE));
	}
}

bool Subcircuit::update(vec4<bool> neighbours, DIR sourceDir)
{
	auto circuitInputs = c.getInputs();
	for (int i = 0; i < inputPinsCount(); i++) {
		auto in = inputs[i].lock();
		circuitInputs[i]->setState(in->getState(NONE));
	}

	return false;
}

int Subcircuit::outputPinsCount() const {
	return c.getOutputs().size();
}

int Subcircuit::inputPinsCount() const {
	return c.getInputs().size();
}

int Subcircuit::getSizeX() const{
	int maxPins = inputPinsCount() > outputPinsCount() ? inputPinsCount() : outputPinsCount();

	if (maxPins > 2) {
		return 3 + 2 * (maxPins-2);
	}
	else {
		return 3;
	}
}

int Subcircuit::getSizeY() const{
	return 3;
}