#include <imgui.h>

#include <functional>
#include <fstream>
#include <iostream>
#include <string>

#include "Rendering/Window/Event.h"
#include "Rendering/Renderers/ChunkRenderer.h"
#include "Rendering/Renderers/DebugRenderer.h"
#include "Rendering/Window/SFMLWindow.h"
#include "Simulation/Component.h"
#include "UI/UIPanel.h"
#include "UI/SimulationManager.h"
#include "UI/ChunkViewEditorPanel.h"
#include "UI/WorkspacePanel.h"
#include "UI/PalettePanel.h"
#include "UI/ValidationPanel.h"
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

        ChunkViewEditorPanel* chunkView = reinterpret_cast<ChunkViewEditorPanel*>(panels.emplace_back(std::make_unique<ChunkViewEditorPanel>("Editor", palettePanel)).get());
		chunkView->setSchematic(workspace.getSchematic(0));

        workspacePanel.registerEventHandler(I_SchematicChanged, [=](Event* e) {
            chunkView->dispatchEvent(e);
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

		ImGui::Begin("Debug");
		ImGui::Checkbox("Debug Chunks:", &Debug::drawDebugChunks);
		ImGui::End();
	}
};


int main()
{
	App app;
	app.run();

	return 0;
}

