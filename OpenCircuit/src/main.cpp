#include <imgui.h>
#include <functional>

#include "Rendering/Window/Event.h"
#include "Rendering/Renderers/ChunkRenderer.h"
#include "Rendering/Window/window.h"
#include "Simulation/Chunk.h"
#include "Simulation/Schematic.h"

#include <iostream>>


class App {
	Window w;

	int rightBrush = 0, leftBrush = 1;

	void drawImGui() {
		ImGui::Begin("Pallette");
	
		ImGui::End();
	}

	Chunk* currentChunk;

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
	}

	void run() {
		while (w.isOpen()) {
			w.imGuiBegin();
			w.handleEvents();

			w.beginDraw();


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

