#include <imgui.h>

#include <functional>
#include <fstream>
#include <iostream>
#include <string>

#include "Rendering/Window/Event.h"
#include "Rendering/Renderers/ChunkRenderer.h"
#include "Rendering/Window/SFMLWindow.h"
#include "Simulation/Component.h"
#include "UI/UIPanel.h"
#include "UI/SimulationManager.h"
#include "UI/ChunkViewPanel.h"
#include "UI/WorkspacePanel.h"
#include "UI/PalettePanel.h"
#include "Workspace.h"

class App {
	SFMLWindow w;

	int autoTickState = 0;

    std::vector<std::unique_ptr<UIPanel>> panels;
    SimulationManager simManager;
    WorkspacePanel workspacePanel;
    PalettePanel palettePanel;

	Workspace workspace;
	
public:

	App() : w(1920, 1080), simManager(workspace), workspacePanel(workspace) {
		Component::initializeComponenets();

        panels.emplace_back(std::make_unique<ChunkViewPanel>(*workspace.getChunk(), palettePanel, workspacePanel, workspace));

		for (int i = 0; i < 6; i++) {
			w.addEventCallback(EventCode::D_Num1 + i, [&, i](Event* e) { palettePanel.setLeftBrush(i + 1); });
		}
	}

	void run() {
		while (w.isOpen()) {
			w.handleEvents();

			w.beginDraw();
			w.imGuiBegin();
			drawImGui();
			w.imGuiDraw();

			w.endDraw();

			if (simManager.doAutotick()) {
				autoTickState++;
				if (autoTickState > simManager.getAutotickAmount()) {
					autoTickState = 0;
					workspace.getChunk()->tick();
				}
			}
		}
	}
	
private:
	void openWorkspaceWindow() {
	}

	void newWorkspace() {
	}

	void drawImGui() {
		const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
		ImGui::DockSpaceOverViewport();

        for(auto& child : panels) {
            child->render();
        }
        
        simManager.render();

        workspacePanel.render();

        palettePanel.render();

        ImGui::ShowDebugLogWindow();
	}
};


int main()
{
	App app;
	app.run();

	return 0;
}

