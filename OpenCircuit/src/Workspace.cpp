#include "Workspace.h"

Workspace::Workspace() 
{
	schematics.emplace_back("Base schematic");
	workingChunk = Chunk(schematics[0]);
}

Schematic* Workspace::getSchematic(int i)
{
	return &(schematics[i]);
}

Schematic* Workspace::getSchematic() {
	return workingChunk.schematic;
}


Chunk* Workspace::getChunk() {
	return &workingChunk;
}

void Workspace::deleteSchematic(int i)
{
	/*
	if (i == workingSchematic)
		workingSchematic = 0;
	
	if(schematics.size() > 1){
		if (i < workingSchematic)
			workingSchematic = 0;
		schematics.erase(schematics.begin() + i);		
	}
	*/
}

void Workspace::setWorkingSchematic(int i)
{
	workingChunk = Chunk(schematics[i]);
	workingChunkId = i;
}

int Workspace::schematicCount()
{
	return schematics.size();
}

void Workspace::newSchematic(std::string name)
{
	schematics.emplace_back(name);
	setWorkingSchematic(schematics.size()-1);
}

void Workspace::moveUp(int i) {
	std::swap(schematics[i], schematics[i + 1]);
	setWorkingSchematic(workingChunkId);
}

int Workspace::getWorkingChunk()
{
	return workingChunkId;
}

void Workspace::placeSubcircuit(int x, int y, int sid) {
	Schematic& s = *getSchematic(sid);
	getSchematic()->placeSubcircuit(x, y, s);
	workingChunk.reset();
}

void Workspace::paint(int gridx, int gridy, int id)
{
	if (workingChunk.schematic->getCellId(gridx, gridy) != 999)
		workingChunk.schematic->setComponent(id, gridx, gridy);
	else if (id == 0)
		workingChunk.schematic->deleteSubcircuit(gridx, gridy);
}
