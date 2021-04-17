#include "Workspace.h"

Workspace::Workspace()
{
	newSchematic("Base schematic");
}

Schematic* Workspace::getSchematic(int i)
{
	return &schematics[i];
}


Schematic* Workspace::getSchematic()
{
	return workingSchematic;
}

void Workspace::setWorkingSchematic(int i)
{
	workingSchematic = &schematics[i];
}


int Workspace::schematicCount()
{
	return schematics.size();
}

void Workspace::newSchematic(std::string name)
{
	for (int i = 0; i < schematics.size(); i++) {
		if (schematics[i].getName() == name) {
			schematics[i].clearChunk();
			return;
		}
	}
	schematics.emplace_back(name);

	workingSchematic = &schematics.back();
}

void Workspace::paint(int gridx, int gridy, int id)
{
	workingSchematic->getChunk()->setComponent(id, gridx, gridy);
}
