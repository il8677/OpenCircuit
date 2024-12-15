#pragma once
#include "UIPanel.h"
#include <Validation/ValidationSet.h>

class Chunk;
class ValidationPanel : public UIPanel {
public:
    ValidationPanel(Chunk& c);

private:
    virtual void onImGuiDraw();

	std::string m_latestResult;

	size_t m_selectedCase = -1;

	Chunk& m_activeChunk;
};