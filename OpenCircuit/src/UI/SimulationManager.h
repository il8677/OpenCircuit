#include "UIPanel.h"

class Workspace;

class SimulationManager : public UIPanel {
public:
    SimulationManager(Workspace& ws) : m_workspace(ws){}

    bool doAutotick() { return m_doAutotick; }
    int  getAutotickAmount() { return m_autoTickAmount; }

private:
    void onImGuiDraw() override;

    Workspace& m_workspace;

	bool m_doAutotick = false;
	int  m_autoTickAmount = 60;
};