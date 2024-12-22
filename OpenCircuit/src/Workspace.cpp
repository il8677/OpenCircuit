#include "Workspace.h"
#include <utility/Serialization.h>

#include <sstream>
#include <fstream>

Workspace::Workspace() 
{
	schematics.push_back(new Schematic("Base schematic"));
}

Schematic* Workspace::getSchematic(int i)
{
	return schematics[i];
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
}

void Workspace::moveUp(int i) {
	std::swap(schematics[i], schematics[i + 1]);
}

void Workspace::save(std::ofstream& fs)
{
	if(notes != "") {
		fs << SER_NOTE_DELIM; fs << notes; fs << SER_NOTE_DELIM;
	}

	for (int i = 0; i  < schematics.size(); i++) {
		fs << schematics[i]->getName() << SER_SCHEM_NAME_DELIM;
		schematics[i]->save(fs);
		fs << SER_SCHEM_END_DELIM;
	}
}

void Workspace::load(std::ifstream& fs) {
    schematics.clear();

	if(fs.peek() == SER_NOTE_DELIM) {
		fs.seekg(1, std::ios::cur);
		getline(fs, notes, SER_NOTE_DELIM);
	}

	std::string line;
	while (getline(fs, line, SER_SCHEM_END_DELIM)) {
		std::istringstream ls(line);
		std::string name;
		std::string schematicline;

		getline(ls, name, SER_SCHEM_NAME_DELIM);
		getline(ls, schematicline, SER_SCHEM_NAME_DELIM);

		newSchematic(name);
		std::istringstream sl(schematicline);
		schematics.back()->load(sl, schematics);
	}
}