#pragma once
#include "UIPanel.h"
#include <Validation/ValidationSet.h>

class ValidationPanel : public UIPanel {
public:
    ValidationPanel();

private:
    virtual void onImGuiDraw();

	std::vector<ValidationSet> m_sets;

	size_t m_selectedSet = -1;
	size_t m_selectedCase = -1;
};