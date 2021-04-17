#include <imgui.h>
#include <functional>

#include "Rendering/Window/Event.h"
#include "Rendering/Renderers/ChunkRenderer.h"
#include "Rendering/Window/window.h"
#include "Workspace.h"

#include <iostream>
#include <string>

// TODO: Do something much better than this
ImVec4 vec4ToImVec4(vec4<unsigned char> v4) {
	return ImVec4(v4.x / 255.0f, v4.y / 255.0f, v4.z / 255.0f, v4.w / 255.0f);
}

class App {
	Window w;
	int rightBrush = 0, leftBrush = 1;

	Workspace workspace;

	//Handler for mouse down events, paints targeted square
	void paint(int screenposX, int screenPosY, bool right) {
		w.screenToWorld(screenposX, screenPosY);
		ChunkRenderer::worldToGrid(screenposX, screenPosY);

		int resultComponent = right ? rightBrush : leftBrush;
		workspace.paint(screenposX, screenPosY, resultComponent);
	}
	
	void mouseDownHandler(Event* e) {
		MouseButtonEvent* mbe = (MouseButtonEvent*) e;

		int targetX = mbe->posx;
		int targetY = mbe->posy;

		paint(targetX, targetY, mbe->id == EventCode::M_RightDown);
	}

	//Handler for mouse move
	void mouseMoveHandler(Event* e) {
		MouseMovedEvent* mbe = (MouseMovedEvent*) e;

		if (mbe->rightDown || mbe->leftDown)
			paint(mbe->posx, mbe->posy, mbe->rightDown);
	}

public:

	App() : w(1920, 1080){
		Component::initializeComponenets();

		w.addEventCallback(EventCode::M_LeftDown, [this](Event* e) {mouseDownHandler(e); });
		w.addEventCallback(EventCode::M_RightDown, [this](Event* e) {mouseDownHandler(e); });
		w.addEventCallback(EventCode::M_MouseMove, [this](Event* e) {mouseMoveHandler(e); });

		//This is probably bad practice (or at least weird), but I was too lazy to write a proper event system
		for (int i = 0; i < 5; i++) {
			w.addEventCallback(EventCode::D_Num1 + i, [this, i](Event* e) {leftBrush = i + 1; });
		}
	}

	void run() {
		while (w.isOpen()) {
			w.handleEvents();

			w.beginDraw();

			ChunkRenderer::Render(w, workspace.getSchematic()->getChunk());

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
		ImGuiWindowFlags menuBarFlags =
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoResize   |
			ImGuiWindowFlags_NoNav      |
			ImGuiWindowFlags_NoMove     |
			ImGuiWindowFlags_MenuBar;


		ImGui::Begin("Pallette");
		//Bad practice but whatever
		static char* componentTooltips[6] = { "Nothing", "Wire", "Input", "Output", "Transistor", "Not" };
		for (int i = 1; i < 6; i++) {
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

		ImGui::Begin("Simulation Manager");
		ImGui::Text("Inputs");
		std::vector<Input*> inputs = workspace.getSchematic()->getChunk()->getInputs();
		for (int i = 0; i < inputs.size(); i++) {
			ImGui::PushID(i);
			if (i > 0)
				ImGui::SameLine();
			if (ImGui::Checkbox(" ", inputs[i]->getStatePointer())) {
				workspace.getSchematic()->getChunk()->updateInputs();
			}
			ImGui::PopID();
		}

		ImGui::Text("Outputs");
		std::vector<Output*> outputs = workspace.getSchematic()->getChunk()->getOutputs();
		for (int i = 0; i < outputs.size(); i++) {
			if (i > 0)
				ImGui::SameLine();
			ImGui::Text("%d", outputs[i]->getState(NONE));
		}

		ImGui::Text("Controls");
		if (ImGui::Button("Reset")) {
			workspace.getSchematic()->getChunk()->reset();
		}
		if (ImGui::Button("Tick")) {
			workspace.getSchematic()->getChunk()->tick();
		}
		ImGui::End();

		ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkSize.x - 250, main_viewport->WorkPos.y), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(250,400));
		ImGui::Begin("Workspace", NULL, menuBarFlags);
		ImGui::Text("Schematics");

		if (ImGui::CollapsingHeader("New schematic")) {
			static char newSchematicName[20];
			ImGui::InputText("Name", newSchematicName, 20);
			if (ImGui::Button("Create")) {
				workspace.newSchematic(std::string(newSchematicName));
			}
		}

		if (ImGui::CollapsingHeader("Edit schematics")) {
			for (int i = 0; i < workspace.schematicCount(); i++) {
				ImGui::Text(workspace.getSchematic(i)->getName().c_str());
				ImGui::SameLine();

				ImGui::PushID(i);
				if (ImGui::Button("Edit")) {
					workspace.setWorkingSchematic(i);
				}
				if (i > 0) {
					ImGui::SameLine();
					if (ImGui::Button("x")) {
						workspace.deleteSchematic(i);
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
	}


};


int main()
{
	App app;
	app.run();

	return 0;
}

