#include <map>

#include "Chunk.h"
#include "Subcircuit.h"

#define M_UP x, y - 1
#define M_RIGHT x + 1, y
#define M_DOWN x, y + 1
#define M_LEFT x - 1, y

std::vector<Input*> Chunk::getInputs() const
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

std::vector<Output*> Chunk::getOutputs() const
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
	if (x >= 0 && y >= 0 && y < CHUNK_Y && x < CHUNK_X)
		return cMap[x][y]->id();
}

void Chunk::setComponent(Component* c, int x, int y) {
	if (x >= 0 && y >= 0 && y < CHUNK_Y && x < CHUNK_X) {
		cMap[x][y] = c;
	}
}

void Chunk::setComponent(int cid, int x, int y)
{
	setComponent(Component::components[cid]->copy(), x, y);
}


void Chunk::placeSubcircuit(int xstart, int ystart, Schematic& s)
{
	Subcircuit* sc = new Subcircuit(s);


	const int xend = xstart + sc->getSizeX();
	const int yend = ystart + sc->getSizeY();

	if (xend < CHUNK_X && yend < CHUNK_Y) {
		//Place foundation
		for (int x = xstart; x < xend; x++) {
			for (int y = ystart; y < yend; y++) {
				cMap[x][y] = (Component*)sc;
			}
		}
		//Place 'inputs'
		for (int i = 0; i < sc->inputPinsCount()*2; i += 2) {
			Wire* wirePlacement = new Wire();
			cMap[xstart-1][ystart + i] = (Component*)wirePlacement;
			sc->addInput(&cMap[xstart - 1][ystart + i]);
		}
		//Place 'outputs'
		for (int i = 0; i < sc->outputPinsCount()*2; i += 2) {
			Constant* constantPlacement = new Constant();
			cMap[xend][ystart + i] = constantPlacement;
			sc->addOutput(&cMap[xend][ystart + i]);
		}

		subcircuits.push_front(sc);
	}
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
	return vec4<bool>(getState(M_UP, DOWN), getState(M_RIGHT, LEFT), getState(M_DOWN, UP), getState(M_LEFT, RIGHT));
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

	for (auto it = subcircuits.begin(); it != subcircuits.end(); ++it) {
		(*it)->getSchematic().getChunk()->reset();
		(*it)->getSchematic().getChunk()->updateInputs();
	}

	for (int x = 0; x < CHUNK_X; x++) {
		for (int y = 0; y < CHUNK_Y; y++) {
			if (cMap[x][y]->id() == 2)
				createUpdatesAround(x, y);
			else if (cMap[x][y]->id() == 5)
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

	for (std::forward_list<Subcircuit*>::iterator it = subcircuits.begin(); it != subcircuits.end(); ++it) {
		(*it)->tick();
	}
}

void Chunk::clear()
{
	for (int x = 0; x < CHUNK_X; x++) {
		for (int y = 0; y < CHUNK_Y; y++) {
			if (cMap[x][y]->id() != 0) {
				delete cMap[x][y];
				cMap[x][y] = new Component();
			}
		}
	}
}

Chunk::Chunk() {
	for (int x = 0; x < CHUNK_X; x++) {
		for (int y = 0; y < CHUNK_Y; y++){
			cMap[x][y] = new Component();
		}
	}

}

Chunk::~Chunk() {
	for (int x = 0; x < CHUNK_X; x++) {
		for (int y = 0; y < CHUNK_Y; y++) {
			delete cMap[x][y];
		}
	}
}

Chunk::Chunk(const Chunk& original) {
	std::map<Component*, Component*> processedComponents;


	for (int x = 0; x < CHUNK_X; x++)
		for (int y = 0; y < CHUNK_Y; y++)
			cMap[x][y] = 0;

	for (int x = 0; x < CHUNK_X; x++) {
		for (int y = 0; y < CHUNK_Y; y++) {
			Component* c = original.cMap[x][y];
			if (cMap[x][y] == nullptr) { //If the component isn't nullptr, it's part of a subcircuit, so should be ignored
				if (c->id() == 999) {
					placeSubcircuit(x, y, ((Subcircuit*)c)->getSchematic());
				}
				else if (processedComponents.find(c) == processedComponents.end()) {
					cMap[x][y] = c->copy();
					processedComponents[c] = cMap[x][y];
				}
				else {
					cMap[x][y] = processedComponents[c];
				}
			}
		}
	}
}

std::vector<Component*> Component::components;