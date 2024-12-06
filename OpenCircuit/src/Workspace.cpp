#include "Workspace.h"

#include <sstream>
#include <fstream>

Workspace::Workspace() 
{
	schematics.push_back(new Schematic("Base schematic"));
	workingChunk = Chunk(schematics[0]);
}

Schematic* Workspace::getSchematic(int i)
{
	return schematics[i];
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
	for (int i = 0; i < schematics.size(); i++) {
		if (schematics[i]->getName() == name) {
			delete schematics[i];
			schematics[i] = new Schematic(name);
			return;
		}
	}

	schematics.push_back(new Schematic(name));
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

void Workspace::save(std::ofstream& fs)
{
	for (int i = 0; i  < schematics.size(); i++) {
		fs << schematics[i]->getName() << ";";
		schematics[i]->save(fs);
		fs << ":";
	}
}

void Workspace::load(std::ifstream& fs) {
    schematics.clear();
	std::string line;
	while (getline(fs, line, ':')) {
		std::istringstream ls(line);
		std::string name;
		std::string schematicline;

		getline(ls, name, ';');
		getline(ls, schematicline, ';');

		newSchematic(name);
		std::istringstream sl(schematicline);
		schematics.back()->load(sl, schematics);
	}
}