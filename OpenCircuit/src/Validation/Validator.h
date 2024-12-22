#pragma once

#include <vector>

class ValidationSet;
class Schematic;
class Chunk;
class Validator {
public:
	std::vector<bool> validate(ValidationSet&, Schematic&);
	std::vector<bool> validate(ValidationSet&, Chunk&);
};