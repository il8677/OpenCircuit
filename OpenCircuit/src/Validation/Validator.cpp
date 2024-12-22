#include "Validator.h"

#include "ValidationSet.h"
#include <Simulation/Chunk.h>

std::vector<bool> Validator::validate(ValidationSet& validatorSet, Chunk& c) {
	std::vector<bool> result(validatorSet.getTestCaseCount());
	
	std::vector<char*> chunkInputs = c.getInputs();
	std::vector<char*> chunkOutputs = c.getOutputs();

	TestCaseTransformer& transformer = validatorSet.getTransformer();

	for(size_t i = 0; i < validatorSet.getTestCaseCount(); i++) {
		TestCase tc = validatorSet.getTestCase(i);

		std::vector<bool> input = transformer.getInput(tc.input);

		for(size_t j = 0; j < chunkInputs.size(); j++) {
			*chunkInputs[j] = input[j];
		}

		for(size_t tick = 0; tick < validatorSet.tickRequirement; tick++) {
			c.tick();
		}

		std::vector<bool> output;

		for(char* out : chunkOutputs) {
			output.push_back(*out);
		}

		std::string strOutput = transformer.convertOutput(output);

		result[i] = strOutput == tc.expectedOutput;
	}

	return result;
}

std::vector<bool> Validator::validate(ValidationSet& validatorSet, Schematic& schematic) {
	Chunk c(&schematic);
	return validate(validatorSet, c);
}