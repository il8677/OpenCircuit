#include "ChunkViewPanel.h"
#include "../Simulation/Chunk.h"

class PalettePanel;
class WorkspacePanel;
class SimulationManager;
class Workspace;

class ChunkViewEditorPanel : public ChunkViewPanel {
public:
	ChunkViewEditorPanel(std::string name, PalettePanel& palettePanel); 
    
	void setSelectedScematic(Schematic* schematic);

private:
	virtual void onImGuiDraw() override;
	void setupEvents();

	PalettePanel& m_palettePanel;
	SimulationManager& m_simulationManager;
	Chunk m_chunk;
	
	Schematic* m_selectedSchematic=nullptr;

	int autoTickState = 0;

	
};