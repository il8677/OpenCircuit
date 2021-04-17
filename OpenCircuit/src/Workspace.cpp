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
	return &schematics[workingSchematic];
}
void Workspace::deleteSchematic(int i)
{
	if (i == workingSchematic)
		workingSchematic = 0;
	
	if(schematics.size() > 1){
		if (i < workingSchematic)
			workingSchematic = 0;
		schematics.erase(schematics.begin() + i);		
	}
}

void Workspace::setWorkingSchematic(int i)
{
	workingSchematic = i;
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

	workingSchematic = schematics.size()-1;
}

void Workspace::paint(int gridx, int gridy, int id)
{
	schematics[workingSchematic].getChunk()->setComponent(id, gridx, gridy);
}
