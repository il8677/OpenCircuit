#pragma once

#include <vector>

class ValidationSet;
class Schematic;
class Validator {
public:
	std::vector<bool> validate(ValidationSet&, Schematic&);
};