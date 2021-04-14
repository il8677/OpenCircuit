#include <imgui.h>
#include <functional>

#include "Rendering/Window/Event.h"
#include "Rendering/Renderers/ChunkRenderer.h"
#include "Rendering/Window/window.h"
#include "Simulation/Chunk.h"
#include "Simulation/Schematic.h"

class App {
	Window w;

	int rightBrush = 0, leftBrush = 1;

	ChunkRenderer testRenderer;
	Chunk testChunk;

	void drawImGui() {
		ImGui::Begin("Pallette");
	
		ImGui::End();
	}

	void paint(Event * e) {
		MouseButtonEvent* mbe = (MouseButtonEvent*) e;

		int targetX = mbe->posx;
		int targetY = mbe->posy;

		w.screenToWorld(targetX, targetY);
		testRenderer.worldToGrid(targetX, targetY);

		int resultComponent = mbe->id == EventCode::LeftDown ? leftBrush : rightBrush;
		testChunk.setComponent(resultComponent, targetX, targetY);
	}

public:

	App() : w(1920, 1080), testRenderer(testChunk){
		Component::initializeComponenets();

		w.addEventCallback(EventCode::LeftDown, [this](Event* e) {paint(e); });
		w.addEventCallback(EventCode::RightDown, [this](Event* e) {paint(e); });
	}

	void run() {

		testChunk.setComponent(new Wire(), 0, 0);
		testChunk.setComponent(new Wire(), 31, 31);
		testChunk.setComponent(new Wire(), 31, 0);
		testChunk.setComponent(new Wire(), 0, 31);
		while (w.isOpen()) {
			w.imGuiBegin();
			w.handleEvents();

			w.beginDraw();

			testRenderer.Render(w);

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

