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

    std::vector<std::unique_ptr<UIPanel>> panels;
    WorkspacePanel workspacePanel;
    PalettePanel palettePanel;

	Workspace workspace;
	
public:

	App() : w(1920, 1080), workspacePanel(workspace) {
		Component::initializeComponenets();

        ChunkViewPanel* chunkView = reinterpret_cast<ChunkViewPanel*>(panels.emplace_back(std::make_unique<ChunkViewPanel>(*workspace.getChunk(), palettePanel)
).get());

        workspacePanel.registerEventHandler(I_SchematicChanged, [=](Event* e) {
            SchematicChangedEvent* sce = reinterpret_cast<SchematicChangedEvent*>(e);

            chunkView->setSchematic(sce->changedSchematic);
        });

		workspacePanel.registerEventHandler(I_SchematicPlaced, [=](Event* e) {
			SchematicPlaceEvent* spe = reinterpret_cast<SchematicPlaceEvent*>(e);
			
			chunkView->setSelectedScematic(spe->placedSchematic);
		});


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

