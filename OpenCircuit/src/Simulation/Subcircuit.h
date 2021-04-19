#pragma once
#include "Component.h"
#include "Chunk.h"

class Subcircuit : Component
{
public: 
	virtual int id() override { return 7; } 
	virtual Component* copy() override { 
		throw 1;
	}

	Subcircuit(Chunk& containedChunk);
};

