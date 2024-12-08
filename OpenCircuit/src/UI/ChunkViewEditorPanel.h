#include "ChunkViewPanel.h"
#include "../Simulation/Chunk.h"

class PalettePanel;
class WorkspacePanel;
class SimulationManager;
class Workspace;

class ChunkViewEditorPanel : public ChunkViewPanel {
public:
	ChunkViewEditorPanel(PalettePanel& palettePanel); 
    void setSchematic(Schematic* schematic);
	void setSelectedScematic(Schematic* schematic);

private:
	virtual void onImGuiDraw() override;
	void setupEvents();

	EventManager m_eventManager;

	PalettePanel& m_palettePanel;
	SimulationManager& m_simulationManager;
	Chunk m_chunk;

	Schematic* m_selectedSchematic=nullptr;
	Chunk* m_popupChunk=nullptr;

	int autoTickState = 0;

	// Rendering stuff
	ImVec2 m_viewportSize;
	sf::RenderTexture m_texture;
	sf::RenderTexture m_popupTexture;
};