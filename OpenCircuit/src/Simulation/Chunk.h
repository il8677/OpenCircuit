#pragma once
#include <memory>
#include <vector>
#include <queue>
#include <forward_list>

#include "Component.h"
#include "Job.h"
#include "../Utility/vec4.h"

#define CHUNK_X 10
#define CHUNK_Y 10

class Subcircuit;
class Schematic;

//0 = nothing
//1 = wire
//2 = input
//3 = outputs
//4 = transistor
//5 = ntransistor
class Chunk
{
	friend class Debug;
	// TODO: use shared_ptr
	Component* cMap[CHUNK_X][CHUNK_Y];
	std::queue<Job> jobQueue;

	std::forward_list<Subcircuit*> subcircuits;

	inline void createUpdateJob(int x, int y, DIR d);

	inline void createUpdatesAround(int x, int y);

	inline vec4<bool> getNeighbours(int x, int y) const;

protected:

public:
	std::vector<Input*>  getInputs() const;
	std::vector<Output*> getOutputs() const;

	int getCellId(int x, int y) const;
	inline bool getState(int x, int y, DIR from=NONE) const;

	void setComponent(Component* c, int x, int y);
	void setComponent(int cid, int x, int y);

	void placeSubcircuit(int x, int y, Schematic& s);

	//Creates an update job around all the input cells
	void updateInputs();
	void reset();

	//Propogate jobs
	void tick();
	void clear();

	Chunk();
	~Chunk();

	//Copy constructor, peforms deep copy creating new objects contained by shared_ptrs
	Chunk(const Chunk&);
};