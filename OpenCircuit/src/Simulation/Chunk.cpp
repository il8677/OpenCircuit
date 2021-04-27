#include <map>

#include "Chunk.h"
#include "Subcircuit.h"
#include "Component.h"      // for Component, Constant, Wire, Component::components, Input, Output
#include "Schematic.h"      // for Schematic
#include "Job.h"

#define M_UP x, y - 1
#define M_RIGHT x + 1, y
#define M_DOWN x, y + 1
#define M_LEFT x - 1, y


void Chunk::createUpdatesAround(int x, int y) {
	createUpdateJob(M_UP, DIR::DOWN);
	createUpdateJob(M_RIGHT, DIR::LEFT);
	createUpdateJob(M_DOWN, DIR::UP);
	createUpdateJob(M_LEFT, DIR::RIGHT);
}

bool Chunk::getOutput(int x, int y, DIR from) const
{
	if (x >= 0 && y >= 0 && y < CHUNK_Y && x < CHUNK_X)
		return schematic->getComponent(x,y)->getOutput(from, states[x][y]);
	return false;
}

inline vec4<bool> Chunk::getNeighbours(int x, int y) const
{
	return vec4<bool>(getOutput(M_UP, DOWN), getOutput(M_RIGHT, LEFT), getOutput(M_DOWN, UP), getOutput(M_LEFT, RIGHT));
}

void Chunk::createUpdateJob(int x, int y, DIR d) {
	if (x >= 0 && y >= 0 && y < CHUNK_Y && x < CHUNK_X) 
		jobQueue.emplace(x, y, d);
}

void Chunk::updateInputs() {

	for (int x = 0; x < CHUNK_X; x++) {
		for (int y = 0; y < CHUNK_Y; y++) {
			if (schematic->getCellId(x,y) == 2) 
				createUpdatesAround(x, y);
		}
	}
}

void Chunk::reset()
{
	for (int x = 0; x < CHUNK_X; x++) {
		for (int y = 0; y < CHUNK_Y; y++) {
			if (schematic->getCellId(x,y) != 2) {
				states[x][y] = 0;
			}
		}
	}

	std::queue<Job> queue;
	std::swap(jobQueue, queue);

	for (int x = 0; x < CHUNK_X; x++) {
		for (int y = 0; y < CHUNK_Y; y++) {
			if (schematic->getCellId(x, y) == 2)
				createUpdatesAround(x, y);
			else if (schematic->getCellId(x,y) == 5)
				createUpdateJob(x, y, NONE);
		}
	}

	populateSubcircuits();
}

std::vector<char*> Chunk::getOutputs()
{
	std::vector<char*> returnVector;

	for (int x = 0; x < CHUNK_X; x++) {
		for (int y = 0; y < CHUNK_Y; y++) {
			if (schematic->getCellId(x, y) == 3)
				returnVector.push_back(&states[x][y]);
		}
	}

	return returnVector;
}

std::vector<char*> Chunk::getInputs()
{
	std::vector<char*> returnVector;

	for (int x = 0; x < CHUNK_X; x++) {
		for (int y = 0; y < CHUNK_Y; y++) {
			if (schematic->getCellId(x, y) == 2)
				returnVector.push_back(&states[x][y]);
		}
	}

	return returnVector;
}

void Chunk::tick() {
	std::queue<Job> queue;
	std::swap(jobQueue, queue);

	while (!queue.empty()) {
		Job& j = queue.front();

		char last = states[j.x][j.y];
		states[j.x][j.y] = schematic->getComponent(j.x, j.y)->predictState(getNeighbours(j.x, j.y), j.d, last);

		bool changed = !(last == states[j.x][j.y]);
		
		queue.pop();
		if(changed) createUpdatesAround(j.x, j.y);
	}

	for (int i = 0; i < subcircuits.size(); i++) {
		//TODO: speed this up (Don't use queue, since searching through the state map is relativley slow
		subcircuits[i].tick();
		std::queue<char*> updateQueue;
		std::swap(updateQueue, subcircuits[i].updatedCells);

		while (!updateQueue.empty()) {
			char* c = updateQueue.front();
			for (int x = 0; x < CHUNK_X; x++) {
				for (int y = 0; y < CHUNK_Y; y++) {
					if (&states[x][y] == c) {
						createUpdatesAround(x, y);
						x = CHUNK_X;
						break;
					}
				}
			}

			updateQueue.pop();
		}
	}
}



Chunk::Chunk(Schematic& usedSchematic){
	schematic = &usedSchematic;
	for (int x = 0; x < CHUNK_X; x++) {
		for (int y = 0; y < CHUNK_Y; y++) {
			states[x][y] = 0;
		}
	}

	populateSubcircuits();
}


void Chunk::populateSubcircuits() {
	subcircuits.clear();

	for (auto it = schematic->subcircuits.begin(); it != schematic->subcircuits.end(); ++it) {
		subcircuits.push_back(Subcircuit((*it)->s));
		for (int i = 0; i < (*it)->inx.size(); i++) {
			subcircuits.back().addInput(&states[(*it)->inx[i]][(*it)->iny[i]]);
		}

		for (int i = 0; i < (*it)->outx.size(); i++) {
			subcircuits.back().addOutput(&states[(*it)->outx[i]][(*it)->outy[i]]);
		}

		//subcircuits.back().reset();
	}
}

Chunk::Chunk(const Chunk& c)
{
	schematic = c.schematic;
	for (int x = 0; x < CHUNK_X; x++) {
		for (int y = 0; y < CHUNK_Y; y++) {
			states[x][y] = c.states[x][y];
		}
	}

	populateSubcircuits();
}

Chunk::Chunk(){

}

Chunk::~Chunk()
{

}

Chunk& Chunk::operator=(const Chunk& other)
{
	schematic = other.schematic;
	for (int x = 0; x < CHUNK_X; x++) {
		for (int y = 0; y < CHUNK_Y; y++) {
			states[x][y] = other.states[x][y];
		}
	}

	populateSubcircuits();
	return *this;
}

std::vector<Component*> Component::components;
