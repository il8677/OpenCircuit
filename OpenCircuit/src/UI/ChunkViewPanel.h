#include <SFML/Graphics.hpp>

#include "UIPanel.h"
#include "../Rendering/Window/EventManager.h"
#include <imgui.h>

class Chunk;
class PalettePanel;
class WorkspacePanel;
class Workspace;

class ChunkViewPanel : public UIPanel {
public:
	ChunkViewPanel(Chunk& chunk, PalettePanel& palettePanel, WorkspacePanel& workspacePanel, Workspace& workspace) : m_chunk(chunk), m_palettePanel(palettePanel), m_workspacePanel(workspacePanel), m_workspace(workspace) { setupEvents(); }

private:
	virtual void onImGuiDraw() override;
	void setupEvents();

	EventManager m_eventManager;

	WorkspacePanel& m_workspacePanel;
	PalettePanel& m_palettePanel;
	Chunk& m_chunk;
	Workspace& m_workspace;

	Chunk* m_popupChunk=nullptr;

	ImVec2 m_viewportSize;
	sf::RenderTexture m_texture;
	sf::RenderTexture m_popupTexture;
};