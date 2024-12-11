#pragma once
#include <vector>
#include <string>

class TestCaseTransformer {
public:
	void setInputLines(size_t lines);
	void setOutputLines(size_t lines);

	void setInputCount(size_t count);
	void setOutputCount(size_t count);

	int getInputLines() { return m_inputLines; }
	int getOutputLines() { return m_outputLines; }

	int getInputCount() { return (int)m_inputLineMapping.size(); }
	int getOutputCount() { return (int)m_outputLineMapping.size(); }
 
	size_t getInputMapping(size_t input) const;
	size_t getOutputMapping(size_t output) const;

	void setInputMapping(size_t input, size_t line) { m_inputLineMapping[input] = line; }

	std::vector<bool> getInput(std::string s);
	std::string convertOutput(std::vector<bool> outputs);

private:
	template<typename T> using PerInput = std::vector<T>;
	template<typename T> using PerOutput = std::vector<T>;

	size_t m_inputLines=1;
	size_t m_outputLines=1;

	PerInput<size_t> m_inputLineMapping;
	PerOutput<size_t> m_outputLineMapping;
};