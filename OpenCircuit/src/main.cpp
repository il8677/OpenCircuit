#include <imgui.h>
#include <functional>

#include "Rendering/Window/Event.h"
#include "Rendering/Renderers/ChunkRenderer.h"
#include "Rendering/Window/window.h"
#include "Simulation/Chunk.h"
#include "Simulation/Schematic.h"

#include <iostream>
#include <string>

// TODO: Do something much better than this
ImVec4 vec4ToImVec4(vec4<unsigned char> v4) {
	return ImVec4(v4.x / 255.0f, v4.y / 255.0f, v4.z / 255.0f, v4.w / 255.0f);
}

class App {
	Window w;
	int rightBrush = 0, leftBrush = 1;

	Chunk* currentChunk;

	void drawImGui() {
		ImGui::Begin("Pallette");
		//Bad practice but whatever
		static char* componentTooltips[6] = {"Nothing", "Wire", "Input", "Output", "Transistor", "Not"};
		for (int i = 1; i < 6; i++) {
			ImGui::PushID(i);
			ImGui::SameLine();
			ImGui::PushStyleColor(ImGuiCol_Button, vec4ToImVec4(ChunkRenderer::getComponentColour(i)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, vec4ToImVec4(ChunkRenderer::getComponentColour(i)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, vec4ToImVec4(ChunkRenderer::getComponentColour(i)));
			if (ImGui::Button(" ", ImVec2(20,20))) {
				leftBrush = i;
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(componentTooltips[i]);

			ImGui::PopStyleColor(3);
			ImGui::PopID();
		}
		ImGui::End();

		ImGui::Begin("Simulation Manager");
		ImGui::Text("Inputs");
		std::vector<Input*> inputs = currentChunk->getInputs();
		for (int i = 0; i < inputs.size(); i++) {
			ImGui::PushID(i);
			if(i > 0)
				ImGui::SameLine();
			if (ImGui::Checkbox(" ", inputs[i]->getStatePointer())) {
				currentChunk->updateInputs();
			}
			ImGui::PopID();
		}

		ImGui::Text("Outputs");
		std::vector<Output*> outputs = currentChunk->getOutputs();
		for (int i = 0; i < outputs.size(); i++) {
			if (i > 0)
				ImGui::SameLine();
			ImGui::Text("%d", outputs[i]->getState(NONE));
		}

		ImGui::Text("Controls");
		if (ImGui::Button("Reset")) {
			currentChunk->reset();
		}
		if (ImGui::Button("Tick")) {
			currentChunk->tick();
		}
		ImGui::End();
	}

	//Handler for mouse down events, paints targeted square
	void paint(int screenposX, int screenPosY, bool right) {


		w.screenToWorld(screenposX, screenPosY);
		ChunkRenderer::worldToGrid(screenposX, screenPosY);

		int resultComponent = right ? rightBrush : leftBrush;
		currentChunk->setComponent(resultComponent, screenposX, screenPosY);
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

		if (mbe->rightDown || mbe->leftDown) {
			paint(mbe->posx, mbe->posy, mbe->rightDown);
		}
	}

public:

	App() : w(1920, 1080){
		Component::initializeComponenets();

		w.addEventCallback(EventCode::M_LeftDown, [this](Event* e) {mouseDownHandler(e); });
		w.addEventCallback(EventCode::M_RightDown, [this](Event* e) {mouseDownHandler(e); });

		w.addEventCallback(EventCode::M_MouseMove, [this](Event* e) {mouseMoveHandler(e); });

		currentChunk = new Chunk();
	}

	void run() {
		while (w.isOpen()) {
			w.handleEvents();

			w.beginDraw();

			ChunkRenderer::Render(w, *currentChunk);

			w.imGuiBegin();
			drawImGui();
			w.imGuiDraw();

			w.endDraw();
		}

	}
};


int main()
{
	App app;
	app.run();

	return 0;
}

