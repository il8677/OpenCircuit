#include <map>

#include "Chunk.h"
#include "Subcircuit.h"
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

BOOLEAN Chunk::getOutput(int x, int y, DIR from) const
{
	if (x >= 0 && y >= 0 && y < CHUNK_Y && x < CHUNK_X)
		return schematic->getComponent(x,y)->getOutput(from, states[x][y]);
	return FALSE;
}

inline vec4<BOOLEAN> Chunk::getNeighbours(int x, int y) const
{
	return vec4<BOOLEAN>(getOutput(M_UP, DOWN), getOutput(M_RIGHT, LEFT), getOutput(M_DOWN, UP), getOutput(M_LEFT, RIGHT));
}

void Chunk::createUpdateJob(int x, int y, DIR d) {
	if (x >= 0 && y >= 0 && y < CHUNK_Y && x < CHUNK_X) 
		jobQueue.emplace(x, y, d);
}

void Chunk::updateInputs() {

	for (int i = 0; i < inputCoords.size(); i++) {
		createUpdatesAround(inputCoords[i].first, inputCoords[i].second);
	}
}

void Chunk::reset()
{
	for (int y = 0; y < CHUNK_Y; y++) {
		for (int x = 0; x < CHUNK_X; x++) {
			if (schematic->getCellId(x,y) != 2) {
				states[x][y] = 0;
			}
		}
	}

	std::queue<Job> queue;
	std::swap(jobQueue, queue);
	
	for (int i = 0; i < inputCoords.size(); i++) {
		createUpdatesAround(inputCoords[i].first, inputCoords[i].second);
	}

	for (int i = 0; i < notCoords.size(); i++) {
		createUpdateJob(notCoords[i].first, notCoords[i].second, NONE);
	}

	precalculateCells();
	populateSubcircuits();
}

std::vector<char*>& Chunk::getOutputs()
{
	return outputs;
}

std::vector<char*>& Chunk::getInputs()
{
	return inputs;
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
			for (int y = 0; y < CHUNK_Y; y++) {
				for (int x = 0; x < CHUNK_X; x++) {
					if (&states[x][y] == c) {
						createUpdatesAround(x, y);
						x = CHUNK_X;
						y = CHUNK_Y;
					}
				}
			}

			updateQueue.pop();
		}
	}
}

void Chunk::populateSubcircuits() {
	subcircuits.clear();
	subcircuits.reserve(schematic->subcircuitCount);

	for (auto it = schematic->subcircuits.begin(); it != schematic->subcircuits.end(); ++it) {
		subcircuits.emplace_back((*it)->s);
		for (int i = 0; i < (*it)->inx.size(); i++) {
			subcircuits.back().addInput(&states[(*it)->inx[i]][(*it)->iny[i]]);
		}

		for (int i = 0; i < (*it)->outx.size(); i++) {
			subcircuits.back().addOutput(&states[(*it)->outx[i]][(*it)->outy[i]]);
		}

		//subcircuits.back().reset();
	}
}

void Chunk::precalculateCells()
{
	outputs.clear();
	inputs.clear();
	inputCoords.clear();
	notCoords.clear();

	for (int y = 0; y < CHUNK_Y; y++) {
		for (int x = 0; x < CHUNK_X; x++) {
			if (schematic->getCellId(x, y) == 3) {
				outputs.push_back(&states[x][y]);
			}
			else if (schematic->getCellId(x, y) == 2) {
				inputs.push_back(&states[x][y]);
				inputCoords.emplace_back(x, y);
			}
			else if (schematic->getCellId(x, y) == 5){
				notCoords.emplace_back(x, y);
			}
		}
	}

}

Chunk::Chunk(const Chunk& c)
{
	schematic = c.schematic;
	for (int y = 0; y < CHUNK_Y; y++) {
		for (int x = 0; x < CHUNK_X; x++) {
			states[x][y] = c.states[x][y];
		}
	}

	reset();
}

Chunk::Chunk(){
	
}

Chunk::~Chunk()
{

}

Chunk::Chunk(Schematic* usedSchematic) {
	schematic = usedSchematic;
	for (int y = 0; y < CHUNK_Y; y++) {
		for (int x = 0; x < CHUNK_X; x++) {
			states[x][y] = 0;
		}
	}

	reset();
}

Chunk& Chunk::operator=(const Chunk& other)
{
	schematic = other.schematic;
	for (int y = 0; y < CHUNK_Y; y++) {
		for (int x = 0; x < CHUNK_X; x++) {
			states[x][y] = other.states[x][y];
		}
	}

	reset();
	return *this;
}

std::vector<Component*> Component::components;
