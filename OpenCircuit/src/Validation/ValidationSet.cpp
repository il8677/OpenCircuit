#include "ValidationSet.h"
#include <fstream>

void ValidationSet::save(std::ofstream& fs) {
	fs << m_cases.size();
	fs << " ";
	fs << tickRequirement;
	fs << " ";
	fs << m_transformer.getInputLines();
	fs << " ";
	fs << m_transformer.getInputCount();
	fs << " ";
	fs << m_transformer.getOutputLines();
	fs << " ";
	fs << m_transformer.getOutputCount();
	fs << " ";
	for(size_t i = 0; i < m_transformer.getInputCount(); i++) {
		fs << m_transformer.getInputMapping(i) << " ";
	}

	for(size_t i = 0; i < m_transformer.getOutputCount(); i++) {
		fs << m_transformer.getOutputMapping(i);
		fs << " ";
	}

	for(size_t i = 0; i < m_cases.size(); i++) {
		fs << m_cases[i].input << "," << m_cases[i].expectedOutput << ",";
	}
}

void ValidationSet::load(std::istream& is) {
	size_t st;

	is >> st;
	m_cases.resize(st);

	is >> tickRequirement;

	is >> st;
	m_transformer.setInputLines(st);

	is >> st;
	m_transformer.setInputCount(st);


	is >> st;
	m_transformer.setOutputLines(st);

	is >> st;
	m_transformer.setOutputCount(st);

	for(size_t i = 0; i < m_transformer.getInputCount(); i++) {
		is >> st;
		m_transformer.setInputMapping(i, st);
	}

	for(size_t i = 0; i < m_transformer.getOutputCount(); i++) {
		is >> st;
	}

	// Get rid of leading ' '
	is.seekg(1, std::ios::cur);
	for(size_t i = 0; i < m_cases.size(); i++) {
		std::getline(is, m_cases[i].input, ',');
		std::getline(is, m_cases[i].expectedOutput, ',');
	}
}