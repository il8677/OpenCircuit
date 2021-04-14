#include <imgui.h>
#include "Rendering/Renderers/ChunkRenderer.h"
#include "Rendering/Window/window.h"
#include "Simulation/Chunk.h"
#include "Simulation/Schematic.h"

int main()
{
	Window w(1920, 1080);

	Chunk testChunk;
	ChunkRenderer testRenderer(testChunk);

	testChunk.setComponent(new Wire(), 0, 0);
	testChunk.setComponent(new Wire(), 31, 31);
	testChunk.setComponent(new Wire(), 31, 0);
	testChunk.setComponent(new Wire(), 0, 31);
	while (w.isOpen()) {
		w.imGuiBegin();
		w.handleEvents();

		w.beginDraw();

		testRenderer.Render(w);
		
		w.imGuiDraw();
		w.endDraw();
	}

	return 0;
}

