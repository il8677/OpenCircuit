
#include "UIPanel.h"

class Workspace;

class WorkspacePanel : public UIPanel {
public:
    WorkspacePanel(Workspace& workspace) : m_workspace(workspace){}

    int popSelectedSubcircuit() { int ssp = m_subcircuitPlacement; m_subcircuitPlacement = -1; return ssp; }
    bool hasSelectedSubcircuit() const { return m_subcircuitPlacement != -1; }

private:
    virtual void onImGuiDraw();

    Workspace& m_workspace;
    int m_subcircuitPlacement=-1;
};