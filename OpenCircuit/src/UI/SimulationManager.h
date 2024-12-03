
class Workspace;

class SimulationManager {
public:
    SimulationManager(Workspace& ws) : m_workspace(ws){}
    void render();

    bool doAutotick() { return m_doAutotick; }
    int  getAutotickAmount() { return m_autoTickAmount; }

private:
    Workspace& m_workspace;

	bool m_doAutotick = false;
	int  m_autoTickAmount = 60;
};