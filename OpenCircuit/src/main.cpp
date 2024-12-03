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
#include "Workspace.h"

// TODO: Do something much better than this
ImVec4 vec4ToImVec4(vec4<unsigned char> v4) {
	return ImVec4(v4.x / 255.0f, v4.y / 255.0f, v4.z / 255.0f, v4.w / 255.0f);
}

class App {
	SFMLWindow w;
	int rightBrush = 0, leftBrush = 1;

	int autoTickState = 0;

    SimulationManager simManager;

	Workspace workspace;

	int subcircuitPlacement = -1;

	//Handler for mouse down events, paints targeted square
	void paint(int gridPosX, int gridPosY, bool right) {
		
		int resultComponent = right ? rightBrush : leftBrush;
		workspace.paint(gridPosX, gridPosY, resultComponent);
	}
	
	void mouseDownHandler(Event* e) {
		MouseButtonEvent* mbe = (MouseButtonEvent*)e;

		int targetX = mbe->posx;
		int targetY = mbe->posy;


		w.screenToWorld(targetX, targetY);
		ChunkRenderer::worldToGrid(targetX, targetY);

		if (subcircuitPlacement != -1) {
			workspace.placeSubcircuit(targetX, targetY, subcircuitPlacement);
			subcircuitPlacement = -1;
		}
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

	App() : w(1920, 1080), simManager(workspace) {
		Component::initializeComponenets();

		w.addEventCallback(EventCode::M_LeftDown, [this](Event* e) {mouseDownHandler(e); });
		w.addEventCallback(EventCode::M_RightDown, [this](Event* e) {mouseDownHandler(e); });
		w.addEventCallback(EventCode::M_MouseMove, [this](Event* e) {mouseMoveHandler(e); });

		//This is probably bad practice (or at least weird), but I was too lazy to write a proper event system
		for (int i = 0; i < 6; i++) {
			w.addEventCallback(EventCode::D_Num1 + i, [this, i](Event* e) {leftBrush = i + 1; });
		}
	}

	void run() {
		while (w.isOpen()) {
			w.handleEvents();

			w.beginDraw();

			ChunkRenderer::Render(w, workspace.getChunk());

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
		ImGuiWindowFlags menuBarFlags =
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoResize   |
			ImGuiWindowFlags_NoNav      |
			ImGuiWindowFlags_NoMove     |
			ImGuiWindowFlags_MenuBar;

        simManager.render();

		ImGui::Begin("Pallette");
		//Bad practice but whatever
		static char* componentTooltips[7] = { "Nothing", "Wire", "Input", "Output", "Transistor", "Not", "Junction"};
		for (int i = 1; i < 7; i++) {
			ImGui::PushID(i);
			ImGui::SameLine();
			ImGui::PushStyleColor(ImGuiCol_Button, vec4ToImVec4(ChunkRenderer::getComponentColour(i)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, vec4ToImVec4(ChunkRenderer::getComponentColour(i)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, vec4ToImVec4(ChunkRenderer::getComponentColour(i)));
			if (ImGui::Button(" ", ImVec2(20, 20)))
				leftBrush = i;
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(componentTooltips[i]);

			ImGui::PopStyleColor(3);
			ImGui::PopID();
		}
		ImGui::End();


		ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkSize.x - 250, main_viewport->WorkPos.y), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(250,400));
		ImGui::Begin("Workspace", NULL, menuBarFlags);
		ImGui::Text("Schematics");

		if (ImGui::Button("Save")) {
			std::ofstream fs;
			fs.open("save.workspace");
			workspace.save(fs);
			fs.close();
		}
		ImGui::SameLine();
		if (ImGui::Button("Load")) {
			std::ifstream fs;
			fs.open("save.workspace");
			workspace.load(fs);
			fs.close();
		}

		if (ImGui::CollapsingHeader("New schematic")) {
			static char newSchematicName[20];
			ImGui::InputText("Name", newSchematicName, 20);
			if (ImGui::Button("Create")) {
				workspace.newSchematic(std::string(newSchematicName));
			}
		}

		if (ImGui::CollapsingHeader("Edit schematics")) {
			for (int i = workspace.schematicCount()-1; i >= 0; i--) {
				ImGui::PushID(i);
				if (ImGui::Button("^")) {
					workspace.moveUp(i);
				}
				ImGui::SameLine();
				ImGui::Text(workspace.getSchematic(i)->getName().c_str());
				ImGui::SameLine();

				if (ImGui::Button("Edit")) {
					workspace.setWorkingSchematic(i);
				}
				if (i > 0) {
					ImGui::SameLine();
					if (ImGui::Button("x")) {
						workspace.deleteSchematic(i);
					}

				}
				//Subcircuits can only be placed in circuits *below* the current circuit
				if (i < workspace.getWorkingChunk()) {

					ImGui::SameLine();
					if (ImGui::Button("Place")) {
						subcircuitPlacement = i;
					}
				}
				ImGui::PopID();
			}
		}
		ImGui::End();

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

