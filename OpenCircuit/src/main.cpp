#include "Rendering/Window/window.h"

int main()
{
	Window w(1920, 1080);

	while (w.isOpen()) {
		w.handleEvents();
		w.beginDraw();

		w.endDraw();
	}

	return 0;
}

