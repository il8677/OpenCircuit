#pragma once
#include <vector>
#include <queue>
#include <forward_list>

#include "../Utility/vec4.h"
#include "Schematic.h"
#include "Job.h"
#include <memory>

class Subcircuit;

//0 = nothing
//1 = wire
//2 = input
//3 = outputs
//4 = transistor
//5 = ntransistor
class Chunk
{
	std::queue<Job> jobQueue;

	char states[CHUNK_X][CHUNK_Y];

	inline void createUpdateJob(int x, int y, DIR d);
	inline void createUpdatesAround(int x, int y);

	inline vec4<bool> getNeighbours(int x, int y) const;
public:
	//TODO: Figure out a way for this not to be heap allocated
	std::vector<Subcircuit*> subcircuits;

	Schematic& schematic;

	inline bool getOutput(int x, int y, DIR from=NONE) const;

	//Creates an update job around all the input cells
	void updateInputs();
	void reset();

	std::vector<char*> getOutputs();
	std::vector<char*> getInputs();

	//Propogate jobs
	void tick();

	Chunk(Schematic&);
	Chunk(const Chunk&);
	~Chunk();

	Chunk* operator=(const Chunk&);
};