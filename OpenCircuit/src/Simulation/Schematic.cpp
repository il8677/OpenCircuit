#include <map>

#include "Schematic.h"
#include "Subcircuit.h"
#include "Component.h"

Schematic::Schematic(std::string name) : name(name)
{
	for (int x = 0; x < CHUNK_X; x++) {
		for (int y = 0; y < CHUNK_Y; y++) {
			cMap[x][y] = new Component();
		}
	}
}


Schematic::~Schematic() {
	for (int x = 0; x < CHUNK_X; x++) {
		for (int y = 0; y < CHUNK_Y; y++) {
			delete cMap[x][y];
		}
	}
}

Schematic::Schematic(const Schematic& original) {
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



std::string Schematic::getName() {
	return name;
}

std::vector<Input*> Schematic::getInputs() const
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


std::vector<Output*> Schematic::getOutputs() const
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

int Schematic::inputCount()
{
	return 0;
}


int Schematic::getCellId(int x, int y) const
{
	if (x >= 0 && y >= 0 && y < CHUNK_Y && x < CHUNK_X)
		return cMap[x][y]->id();
}

void Schematic::setComponent(Component* c, int x, int y) {
	if (x >= 0 && y >= 0 && y < CHUNK_Y && x < CHUNK_X) {
		cMap[x][y] = c;
	}
}

void Schematic::setComponent(int cid, int x, int y)
{
	setComponent(Component::components[cid]->copy(), x, y);
}

Component* Schematic::getComponent(int x, int y)
{
	return cMap[x][y];
}


void Schematic::placeSubcircuit(int xstart, int ystart, Schematic& s)
{
	SubcircuitProxy* sc = new SubcircuitProxy(s);


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
		for (int i = 0; i < sc->s.inputCount() * 2; i += 2) {
			WireInput* wirePlacement = new WireInput();
			cMap[xstart - 1][ystart + i] = (Component*)wirePlacement;

			sc->inx.push_back(xstart - 1);
			sc->iny.push_back(ystart + i);
		}
		//Place 'outputs'
		for (int i = 0; i < sc->s.outputCount() * 2; i += 2) {
			Constant* constantPlacement = new Constant();
			cMap[xend][ystart + i] = constantPlacement;

			sc->outx.push_back(xend);
			sc->outy.push_back(ystart + i);
		}

		subcircuits.push_front(sc);
	}
}