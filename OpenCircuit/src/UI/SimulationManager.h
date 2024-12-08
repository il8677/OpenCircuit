#include "UIPanel.h"

class Chunk;

class SimulationManager : public UIPanel {
public:
    SimulationManager(Chunk& chunk) : m_chunk(chunk) {}

    bool doAutotick() { return m_doAutotick; }
    int  getAutotickAmount() { return m_autoTickAmount; }

private:
    void onImGuiDraw() override;

    Chunk& m_chunk;

	bool m_doAutotick = false;
	int  m_autoTickAmount = 60;
};