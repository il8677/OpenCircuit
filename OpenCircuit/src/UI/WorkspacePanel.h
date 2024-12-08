
#include "UIPanel.h"

class Workspace;

class WorkspacePanel : public UIPanel {
public:
    WorkspacePanel(Workspace& workspace) : m_workspace(workspace){}

private:
    virtual void onImGuiDraw();

    Workspace& m_workspace;
};