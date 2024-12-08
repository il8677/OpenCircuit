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
	ChunkViewPanel(Chunk& chunk, PalettePanel& palettePanel); 
    void setSchematic(Schematic* schematic);
	void setSelectedScematic(Schematic* schematic);

private:
	virtual void onImGuiDraw() override;
	void setupEvents();

	EventManager m_eventManager;

	PalettePanel& m_palettePanel;
	Chunk& m_chunk;

	Schematic* m_selectedSchematic=nullptr;
	Chunk* m_popupChunk=nullptr;

	// Rendering stuff
	ImVec2 m_viewportSize;
	sf::RenderTexture m_texture;
	sf::RenderTexture m_popupTexture;
};