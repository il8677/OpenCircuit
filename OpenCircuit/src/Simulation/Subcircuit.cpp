#include "Subcircuit.h"
#include "Chunk.h"

void Subcircuit::addInput(char* inp)
{
	inputs.push_back(inp);
}

void Subcircuit::addOutput(char* out)
{
	outputs.push_back(out);
}

Subcircuit::Subcircuit(const Chunk& containedChunk) : containedCircuit(containedChunk) {
	containedCircuit.reset();
}

Subcircuit::Subcircuit(Schematic* containedSchematic) : containedCircuit(containedSchematic) {
	containedCircuit.reset();
}

void Subcircuit::reset()
{
	containedCircuit.reset();
}

void Subcircuit::tick() {
	containedCircuit.tick();

	auto circuitOutputs = containedCircuit.getOutputs();
	for (int i = 0; i < circuitOutputs.size(); i++) {
		if (*outputs[i] != *circuitOutputs[i]) updatedCells.push(outputs[i]);
		*outputs[i] = *circuitOutputs[i];
	}

	auto circuitInputs = containedCircuit.getInputs();
	for (int i = 0; i < circuitInputs.size(); i++) 
		*circuitInputs[i] = *inputs[i];

	containedCircuit.updateInputs();

}

void Subcircuit::setSchematic(Schematic* s)
{
	containedCircuit = Chunk(s);
}

Schematic* Subcircuit::getSchematic()
{
	return containedCircuit.schematic;
}

std::string Subcircuit::getName()
{
	return getSchematic()->getName();
}

