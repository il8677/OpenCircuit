#pragma once
#include "Component.h"
#include "Chunk.h"

#include <memory>
#include <vector>

class Subcircuit : Component
{
	Chunk c;

	std::vector<std::weak_ptr<Wire>> inputs;
	std::vector<std::weak_ptr<Constant>> outputs;

public: 
	virtual int id() override { return 999; } 
	virtual Component* copy() override { 
		throw 1;
	}

	void addInput(std::shared_ptr<Wire>& inp);
	void addOutput(std::shared_ptr<Constant>& out);

	Subcircuit(Chunk& containedChunk);
	
	int outputPinsCount() const;
	int inputPinsCount() const;

	int getSizeX() const;
	int getSizeY() const;
	void tick();

	bool update(vec4<bool> neighbours, DIR sourceDir) override;
};

