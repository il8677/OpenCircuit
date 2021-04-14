#pragma once
#include <vector>
#include <queue>

#include "Component.h"
#include "Job.h"
#include "../Utility/vec4.h"

#define CHUNK_X 16
#define CHUNK_Y 16

//0 = nothing
//1 = wire
//2 = input
//3 = outputs
//4 = transistor
//5 = ntransistor
class Chunk
{
	// TODO: use shared_ptr
	Component* cMap[CHUNK_X][CHUNK_Y];
	std::queue<Job> jobQueue;

	inline void createUpdateJob(int x, int y, DIR d);
	inline void createUpdatesAround(int x, int y);
	
	inline bool getState(int x, int y) const;
	inline vec4<bool> getNeighbours(int x, int y) const;
protected:

public:
	std::vector<Input*>  getInputs();
	std::vector<Output*> getOutputs();

	void setComponent(Component* c, int x, int y);

	//Creates an update job around all the input cells
	void updateInputs();

	//Propogate jobs
	void tick();

	Chunk();
};