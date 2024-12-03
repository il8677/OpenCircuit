
class Workspace;

class WorkspacePanel{
public:
    WorkspacePanel(Workspace& workspace) : m_workspace(workspace){}
    void render();

    int popSelectedSubcircuit() { int ssp = m_subcircuitPlacement; m_subcircuitPlacement = -1; return ssp; }
    bool hasSelectedSubcircuit() const { return m_subcircuitPlacement != -1; }

private:
    Workspace& m_workspace;
    int m_subcircuitPlacement=-1;
};