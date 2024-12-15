#include "TestCaseTransformer.h"

#include <sstream>

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);

    // Use getline to extract tokens separated by the delimiter
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

void TestCaseTransformer::setInputLines(size_t lines){
	m_inputLines = lines;
}

void TestCaseTransformer::setOutputLines(size_t lines) {
	m_outputLines = lines;
}

void TestCaseTransformer::setInputCount(size_t count) {
	m_inputLineMapping.resize(count, 0);
}

void TestCaseTransformer::setOutputCount(size_t count) {
	m_outputLineMapping.resize(count, 0);
}

size_t TestCaseTransformer::getInputMapping(size_t input) const {
	return m_inputLineMapping[input];
}

size_t TestCaseTransformer::getOutputMapping(size_t output) const {
	return m_outputLineMapping[output];
}

std::vector<bool> TestCaseTransformer::getInput(std::string s) {
	std::vector<std::string> lines = split(s, '\n');
	std::vector<int> next(lines.size());
	std::vector<bool> output;

	for(size_t line : m_inputLineMapping) {
		int nextForThisLine = next[line]++;
		output.push_back(lines[line][nextForThisLine] == '0');
	}

	return output;
}

std::string TestCaseTransformer::convertOutput(std::vector<bool> outputs) {
	std::string result;
	result.resize(outputs.size());
	for(size_t i = 0; i < outputs.size(); i++){
		result[i] = outputs[i] ? '1' : '0';
	}
	// TODO: Calculate based on mapping
	return result;
}