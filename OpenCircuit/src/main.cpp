#include "Rendering/Window/window.h"
#include <imgui.h>

int main()
{
	Window w(1920, 1080);

	while (w.isOpen()) {
		w.imGuiBegin();
		w.handleEvents();

		w.beginDraw();

		ImGui::Button("TEST");
		ImGui::Begin("Test Window");

		ImGui::End();

		w.imGuiDraw();
		w.endDraw();
	}

	return 0;
}

