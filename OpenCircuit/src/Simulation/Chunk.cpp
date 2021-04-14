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
			if (cMap[x][y]->id == 2)
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
			if (cMap[x][y]->id == 3)
				returnVector.push_back((Output*)cMap[x][y]);
		}
	}
	return returnVector;
}

void Chunk::setComponent(Component* c, int x, int y) {
	delete cMap[x][y];
	cMap[x][y] = c;
}

void Chunk::createUpdatesAround(int x, int y) {
	createUpdateJob(M_UP, DIR::UP);
	createUpdateJob(M_RIGHT, DIR::RIGHT);
	createUpdateJob(M_DOWN, DIR::DOWN);
	createUpdateJob(M_LEFT, DIR::LEFT);
}

inline bool Chunk::getState(int x, int y) const
{
	if (x >= 0 && y >= 0 && y < CHUNK_Y && x < CHUNK_X)
		return cMap[x][y]->getState();
	return false;
}

inline vec4<bool> Chunk::getNeighbours(int x, int y) const
{
	return vec4<bool>(getState(M_UP), getState(M_RIGHT), getState(M_DOWN), getState(M_LEFT));
}

void Chunk::createUpdateJob(int x, int y, DIR d) {
	if (x >= 0 && y >= 0 && y < CHUNK_Y && x < CHUNK_X) 
		jobQueue.emplace(x, y, d);
}

void Chunk::updateInputs() {
	for (int x = 0; x < CHUNK_X; x++) {
		for (int y = 0; y < CHUNK_Y; y++) {
			if (cMap[x][y]->id == 2) 
				createUpdatesAround(x, y);
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