#ifdef DEBUG
#pragma once
#include <imgui.h>

class Workspace;
class Window;

static class Debug {
public:
	static void drawImGui(Workspace& workspace, Window& w);
};
#endif // DEBUG

