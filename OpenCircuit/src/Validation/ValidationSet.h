#pragma once
#include "TestCaseTransformer.h"
#include "TestCase.h"

#include <string>

class ValidationSet {
public:
	ValidationSet();

	TestCaseTransformer& getTransformer() { return m_transformer; }
	const TestCaseTransformer& getTransformer() const { return m_transformer; }

	void addTestCase() { m_cases.emplace_back(); }
	size_t getTestCaseCount() { return m_cases.size(); }
	TestCase& getTestCase(size_t i) { return m_cases[i]; }

	int tickRequirement=4;
private:
	TestCaseTransformer m_transformer;
	std::vector<TestCase> m_cases;

};