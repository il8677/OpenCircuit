#include <imgui.h>

#include <functional>
#include <fstream>
#include <iostream>
#include <string>

#include "Rendering/Window/Event.h"
#include "Rendering/Renderers/ChunkRenderer.h"
#include "Rendering/Window/SFMLWindow.h"
#include "Simulation/Component.h"
#include "UI/SimulationManager.h"
#include "UI/ChunkViewPanel.h"
#include "UI/WorkspacePanel.h"
#include "UI/PalettePanel.h"
#include "Workspace.h"

class App {
	SFMLWindow w;

	int autoTickState = 0;

    SimulationManager simManager;
    WorkspacePanel workspacePanel;
    PalettePanel palettePanel;
	ChunkViewPanel viewPanel;

	Workspace workspace;
	
public:

	App() : w(1920, 1080), simManager(workspace), workspacePanel(workspace), viewPanel(*workspace.getChunk(), palettePanel, workspacePanel, workspace) {
		Component::initializeComponenets();

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
        simManager.render();

		ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkSize.x - 250, main_viewport->WorkPos.y), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(250,400));
        workspacePanel.render();

        palettePanel.render();
		viewPanel.render();

        ImGui::ShowDebugLogWindow();
	}
};


int main()
{
	App app;
	app.run();

	return 0;
}

