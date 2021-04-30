#include <map>

#include <sstream>

#include "Schematic.h"
#include "Subcircuit.h"
#include "Component.h"


std::string Schematic::getName() {
	return name;
}

std::vector<Input*> Schematic::getInputs() const
{
	std::vector<Input*> returnVector;

	for (int y = 0; y < CHUNK_Y; y++) {
		for (int x = 0; x < CHUNK_X; x++) {
			if (cMap[x][y]->id() == 2)
				returnVector.push_back((Input*)cMap[x][y]);
		}
	}

	return returnVector;
}


std::vector<Output*> Schematic::getOutputs() const
{
	std::vector<Output*> returnVector;

	for (int y = 0; y < CHUNK_Y; y++) {
		for (int x = 0; x < CHUNK_X; x++) {
			if (cMap[x][y]->id() == 3)
				returnVector.push_back((Output*)cMap[x][y]);
		}
	}
	return returnVector;
}

int Schematic::inputCount()
{
	return getInputs().size();
}

int Schematic::outputCount() {
	return getOutputs().size();
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

void Schematic::replace(int x, int y, Component* with) {
	if (cMap[x][y]->id() == 999){
		deleteSubcircuit((SubcircuitProxy*)cMap[x][y]);
	}

	delete cMap[x][y];
	cMap[x][y] = with;
}

void Schematic::deleteSubcircuit(SubcircuitProxy* s) {
	bool found = false;
	for (int y = 0; y < CHUNK_Y; y++) {
		for (int x = 0; x < CHUNK_X; x++) {
			if (cMap[x][y] == s) {
				cMap[x][y] = new Component();
				found = true;
			}
		}
	}
	if (found) {
		subcircuits.remove(s);
		subcircuitCount++;
		delete s;
	}
}

void Schematic::deleteSubcircuit(int x, int y)
{
	if (cMap[x][y]->id() == 999) {
		deleteSubcircuit((SubcircuitProxy*)cMap[x][y]);
	}
}

void Schematic::shift(int amount, int dir)
{

}

void Schematic::placeSubcircuit(int xstart, int ystart, Schematic& s)
{
	SubcircuitProxy* sc = new SubcircuitProxy(&s);


	const int xend = xstart + sc->getSizeX();
	const int yend = ystart + sc->getSizeY();

	if (xend < CHUNK_X && yend < CHUNK_Y) {
		//Place foundation
		for (int x = xstart; x < xend; x++) {
			for (int y = ystart; y < yend; y++) {
				replace(x, y, (Component*)sc);
			}
		}
		//Place 'inputs'
		for (int i = 0; i < sc->s->inputCount() * 2; i += 2) {
			#define XCOORD xstart - 1
			#define YCOORD ystart + i

			if (getCellId(XCOORD, YCOORD) == 0) {
				WireInput* wirePlacement = new WireInput();
				replace(XCOORD, YCOORD, (Component*)wirePlacement);
			}

			sc->inx.push_back(XCOORD);
			sc->iny.push_back(YCOORD);
			
			#undef XCOORD
			#undef YCOORD
		}
		//Place 'outputs'
		for (int i = 0; i < sc->s->outputCount() * 2; i += 2) {
			#define XCOORD xend
			#define YCOORD ystart + i

			if (getCellId(XCOORD, YCOORD) == 0) {
				Constant* constantPlacement = new Constant();
				replace(XCOORD, YCOORD, constantPlacement);
			}

			sc->outy.push_back(YCOORD);
			sc->outx.push_back(XCOORD);

			#undef XCOORD
			#undef YCOORD
		}

		subcircuits.push_front(sc);
		subcircuitCount++;
	}
}

Schematic::Schematic(std::string name) : name(name)
{
	for (int y = 0; y < CHUNK_Y; y++) {
		for (int x = 0; x < CHUNK_X; x++) {
			cMap[x][y] = new Component();
		}
	}
}

Schematic::~Schematic() {
	for (int y = 0; y < CHUNK_Y; y++) {
		for (int x = 0; x < CHUNK_X; x++) {
			delete cMap[x][y];
		}
	}

	for (auto i = subcircuits.begin(); i != subcircuits.end(); ++i) {
		//delete* i;
	}
}


Schematic::Schematic(const Schematic& original) {
	name = original.name;
	for (int y = 0; y < CHUNK_Y; y++)
		for (int x = 0; x < CHUNK_X; x++)
			cMap[x][y] = nullptr;

	for (int y = 0; y < CHUNK_Y; y++) {
		for (int x = 0; x < CHUNK_X; x++) {
			Component* c = original.cMap[x][y];
			if (cMap[x][y] == nullptr) { //If the component isn't nullptr, it's part of a subcircuit, so should be ignored
				if (c->id() == 999) {
					placeSubcircuit(x, y, *((Subcircuit*)c)->getSchematic());
				}
				else {
					cMap[x][y] = c->copy();
				}
			}
		}
	}
	subcircuits = original.subcircuits;
	for (auto i = original.subcircuits.begin(); i != original.subcircuits.end(); ++i) {
		subcircuits.push_front(new SubcircuitProxy(**i));
		subcircuitCount++;
	}


}

Schematic::Schematic(Schematic&& original) noexcept
{
	name = std::move(original.name);

	for (int y = 0; y < CHUNK_Y; y++) {
		for (int x = 0; x < CHUNK_X; x++) {
			cMap[x][y] = original.cMap[x][y];
			original.cMap[x][y] = nullptr;
		}
	}
	subcircuits = original.subcircuits;
	for (auto i = original.subcircuits.begin(); i != original.subcircuits.end(); ++i)
		*i = nullptr;
}

Schematic& Schematic::operator=(const Schematic& o) {
	if (&o == this) {
		return *this;
	}

	name = o.name;

	for (int y = 0; y < CHUNK_Y; y++) {
		for (int x = 0; x < CHUNK_X; x++) {
			delete cMap[x][y];
			cMap[x][y] = o.cMap[x][y]->copy();
		}
	}
	
	for (auto i = o.subcircuits.begin(); i != o.subcircuits.end(); ++i) {
		subcircuits.push_front(new SubcircuitProxy(**i));
		subcircuitCount++;
	}

	return *this;
}


Schematic& Schematic::operator=(Schematic&& o) {
	name = std::move(o.name);

	if (&o == this) {
		return *this;
	}

	for (int y = 0; y < CHUNK_Y; y++) {
		for (int x = 0; x < CHUNK_X; x++) {
			delete cMap[x][y];
			cMap[x][y] = o.cMap[x][y];
			o.cMap[x][y] = nullptr;
		}
	}

	subcircuits = o.subcircuits;
	for (auto i = o.subcircuits.begin(); i != o.subcircuits.end(); ++i)
		*i = nullptr;

	return *this;
}

void Schematic::save(std::ofstream& fs)
{
	for (int y = 0; y < CHUNK_Y; y++) {
		for (int x = 0; x < CHUNK_X; x++) {
			if (getCellId(x, y) != 0 && getCellId(x, y) != 999) {
				fs << x << "," << y << "," << getCellId(x, y);
				fs << '[';
			}
		}
	}

	//WARNING: BAD CODE AHEAD
	for (auto it = subcircuits.begin(); it != subcircuits.end(); ++it) {
		for (int y = 0; y < CHUNK_Y; y++) {
			for (int x = 0; x < CHUNK_X; x++) {
				if (cMap[x][y] == *it) {
					fs << x << "," << y << "," << 999 << ',' << (*it)->s->getName() << '[';
					y = CHUNK_Y + 1;
					x = CHUNK_X + 1;
				}
			}
		}
	}
}

void Schematic::load(std::istringstream& is, std::vector<Schematic*>& schematics) {
	//Messy loading, TODO: Find a cleaner way to load these values
	std::string line;
	while (std::getline(is, line, '[')) {
		std::istringstream linestream(line);
		std::string buffer;
		
		int id;
		int x, y;

		std::getline(linestream, buffer, ',');
		x = std::stoi(buffer);

		std::getline(linestream, buffer, ',');
		y = std::stoi(buffer);

		std::getline(linestream, buffer, ',');
		id = std::stoi(buffer);
	
		if (id == 999) {
			std::getline(linestream, buffer, ',');

			for (int i = 0; i < schematics.size(); i++) {
				if (schematics[i]->getName() == buffer) {
					placeSubcircuit(x, y, *schematics[i]);
					break;
				}
			}
		}
		else {
			cMap[x][y] = Component::getComponentOfId(id);
		}
	}
}