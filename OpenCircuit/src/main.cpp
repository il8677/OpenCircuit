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

	//Handler for mouse down events, paints targeted square
	void paint(int gridPosX, int gridPosY, bool right) {
		
		int resultComponent = right ? palettePanel.getRightBrush() : palettePanel.getLeftBrush();
		workspace.paint(gridPosX, gridPosY, resultComponent);
	}
	
	void mouseDownHandler(Event* e) {
		MouseButtonEvent* mbe = (MouseButtonEvent*)e;

		int targetX = mbe->posx;
		int targetY = mbe->posy;


		w.screenToWorld(targetX, targetY);
		ChunkRenderer::worldToGrid(targetX, targetY);

		if (workspacePanel.hasSelectedSubcircuit())
			workspace.placeSubcircuit(targetX, targetY, workspacePanel.popSelectedSubcircuit());
		else {
			paint(targetX, targetY, mbe->id == EventCode::M_RightDown);
		}
	}

	//Handler for mouse move
	void mouseMoveHandler(Event* e) {
		MouseMovedEvent* mbe = (MouseMovedEvent*) e;

		int targetX = mbe->posx;
		int targetY = mbe->posy;

		w.screenToWorld(targetX, targetY);
		ChunkRenderer::worldToGrid(targetX, targetY);

		if (mbe->rightDown || mbe->leftDown)
			paint(targetX, targetY, mbe->rightDown);
	}

public:

	App() : w(1920, 1080), simManager(workspace), workspacePanel(workspace), viewPanel(*workspace.getChunk()) {
		Component::initializeComponenets();

		w.addEventCallback(EventCode::M_LeftDown, [this](Event* e) {mouseDownHandler(e); });
		w.addEventCallback(EventCode::M_RightDown, [this](Event* e) {mouseDownHandler(e); });
		w.addEventCallback(EventCode::M_MouseMove, [this](Event* e) {mouseMoveHandler(e); });

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

        simManager.render();

		ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkSize.x - 250, main_viewport->WorkPos.y), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(250,400));
        workspacePanel.render();

        palettePanel.render();
		viewPanel.render();


		/*
		//'Menu bar'

		ImGui::Begin("Menu bar", NULL, menuBarFlags);
		ImGui::BeginMenuBar();

		if (ImGui::BeginMenu("File")) {
			}
			if (ImGui::MenuItem("New Workspace"))  newWorkspace();
			if (ImGui::MenuItem("Save Workspace"))  newWorkspace();
			if (ImGui::MenuItem("Open Workspace")) openWorkspaceWindow();
			//if (ImGui::MenuItem("Save")) saveSchematic();

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
		ImGui::End();
		*/
#ifdef DEBUG
		Debug::drawImGui(workspace, w);
#endif // DEBUG
	}
};


int main()
{
	App app;
	app.run();

	return 0;
}

