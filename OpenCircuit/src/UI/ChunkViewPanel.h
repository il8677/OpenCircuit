#include <SFML/Graphics.hpp>

#include "../Rendering/Window/EventManager.h"
#include <imgui.h>

class Chunk;
class PalettePanel;
class WorkspacePanel;
class Workspace;

class ChunkViewPanel {
public:
	ChunkViewPanel(Chunk& chunk, PalettePanel& palettePanel, WorkspacePanel& workspacePanel, Workspace& workspace) : m_chunk(chunk), m_palettePanel(palettePanel), m_workspacePanel(workspacePanel), m_workspace(workspace) { setupEvents(); }

	void render();
private:
	void setupEvents();
	void handleInputs();

	EventManager m_eventManager;

	WorkspacePanel& m_workspacePanel;
	PalettePanel& m_palettePanel;
	Chunk& m_chunk;
	Workspace& m_workspace;

	ImVec2 m_viewportSize;
	sf::RenderTexture m_texture;
};