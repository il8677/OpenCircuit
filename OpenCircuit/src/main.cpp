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
		for (int i = 0; i < 6; i++) {
			if (ImGui::ColorButton(std::to_string(i).c_str(), vec4ToImVec4(ChunkRenderer::getComponentColour(i)))) {

			}
		}
		ImGui::End();
	}

	//Handler for mouse down events, paints targeted square
	void paint(Event * e) {
		MouseButtonEvent* mbe = (MouseButtonEvent*) e;

		int targetX = mbe->posx;
		int targetY = mbe->posy;

		w.screenToWorld(targetX, targetY);
		ChunkRenderer::worldToGrid(targetX, targetY);

		int resultComponent = mbe->id == EventCode::M_LeftDown ? leftBrush : rightBrush;
		currentChunk->setComponent(resultComponent, targetX, targetY);
	}

public:

	App() : w(1920, 1080){
		Component::initializeComponenets();

		w.addEventCallback(EventCode::M_LeftDown, [this](Event* e) {paint(e); });
		w.addEventCallback(EventCode::M_RightDown, [this](Event* e) {paint(e); });

		currentChunk = new Chunk();
	}

	void run() {
		while (w.isOpen()) {
			w.imGuiBegin();
			w.handleEvents();

			w.beginDraw();

			ChunkRenderer::Render(w, *currentChunk);

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

