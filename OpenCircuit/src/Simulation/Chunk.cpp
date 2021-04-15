#include "Chunk.h"

#define M_UP x, y - 1
#define M_RIGHT x + 1, y
#define M_DOWN x, y + 1
#define M_LEFT x - 1, y

std::vector<Input*> Chunk::getInputs()
{
	std::vector<Input*> returnVector;

	for (int x = 0; x < CHUNK_X; x++) {
		for (int y = 0; y < CHUNK_Y; y++) {
			if (cMap[x][y]->id() == 2)
				returnVector.push_back((Input*)cMap[x][y]);
		}
	}

	return returnVector;
}

std::vector<Output*> Chunk::getOutputs()
{
	std::vector<Output*> returnVector;

	for (int x = 0; x < CHUNK_X; x++) {
		for (int y = 0; y < CHUNK_Y; y++) {
			if (cMap[x][y]->id() == 3)
				returnVector.push_back((Output*)cMap[x][y]);
		}
	}
	return returnVector;
}

int Chunk::getCellId(int x, int y) const
{
	return cMap[x][y]->id();
}

void Chunk::setComponent(Component* c, int x, int y) {
	if (x >= 0 && y >= 0 && y < CHUNK_Y && x < CHUNK_X) {
		delete cMap[x][y];
		cMap[x][y] = c;
	}
}

void Chunk::setComponent(int cid, int x, int y)
{
	setComponent(Component::components[cid]->copy(), x, y);
}

void Chunk::createUpdatesAround(int x, int y) {
	createUpdateJob(M_UP, DIR::DOWN);
	createUpdateJob(M_RIGHT, DIR::LEFT);
	createUpdateJob(M_DOWN, DIR::UP);
	createUpdateJob(M_LEFT, DIR::RIGHT);
}

inline bool Chunk::getState(int x, int y, DIR from) const
{
	if (x >= 0 && y >= 0 && y < CHUNK_Y && x < CHUNK_X)
		return cMap[x][y]->getState(from);
	return false;
}

inline vec4<bool> Chunk::getNeighbours(int x, int y) const
{
	return vec4<bool>(getState(M_UP, DOWN), getState(M_RIGHT, LEFT), getState(M_DOWN, RIGHT), getState(M_LEFT, UP));
}

void Chunk::createUpdateJob(int x, int y, DIR d) {
	if (x >= 0 && y >= 0 && y < CHUNK_Y && x < CHUNK_X) 
		jobQueue.emplace(x, y, d);
}

void Chunk::updateInputs() {

	for (int x = 0; x < CHUNK_X; x++) {
		for (int y = 0; y < CHUNK_Y; y++) {
			if (cMap[x][y]->id() == 2) 
				createUpdatesAround(x, y);
		}
	}
}

void Chunk::reset()
{
	for (int x = 0; x < CHUNK_X; x++) {
		for (int y = 0; y < CHUNK_Y; y++) {
			if (cMap[x][y]->id() != 2) {
				cMap[x][y]->setState(0);
			}
		}
	}

	std::queue<Job> queue;
	std::swap(jobQueue, queue);

	for (int x = 0; x < CHUNK_X; x++) {
		for (int y = 0; y < CHUNK_Y; y++) {
			if (cMap[x][y]->id() == 2)
				createUpdatesAround(x, y);
			else if (cMap[x][y]->id() > 4)
				createUpdateJob(x, y, NONE);
		}
	}
}

void Chunk::tick() {
	std::queue<Job> queue;
	std::swap(jobQueue, queue);

	while (!queue.empty()) {
		Job& j = queue.front();

		bool changed = cMap[j.x][j.y]->update(getNeighbours(j.x, j.y), j.d);
		
		queue.pop();
		if(changed) createUpdatesAround(j.x, j.y);
	}
}

Chunk::Chunk() {
	for (int x = 0; x < CHUNK_X; x++) {
		for (int y = 0; y < CHUNK_Y; y++){
			cMap[x][y] = new Component();
		}
	}
}

std::vector<Component* > Component::components;