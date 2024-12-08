#include "ChunkViewEditorPanel.h"

#include "../Simulation/Schematic.h"
#include "../Simulation/Subcircuit.h"

#include "PalettePanel.h"
#include "WorkspacePanel.h"
#include "SimulationManager.h"
#include "../Rendering/Renderers/ChunkRenderer.h"

#include <imgui.h>

void Paint(Chunk& c, int targetX, int targetY, int resultComponent){
	if (c.schematic->getCellId(targetX, targetY) != 999)
		c.schematic->setComponent(resultComponent, targetX, targetY);
	else if (resultComponent == 0)
		c.schematic->deleteSubcircuit(targetX, targetY);
}

ChunkViewEditorPanel::ChunkViewEditorPanel(PalettePanel& palettePanel) : 
	ChunkViewPanel(m_chunk),
	m_palettePanel(palettePanel),
	m_simulationManager(emplaceChild<SimulationManager, Chunk&>(m_chunk)) { 

	setupEvents(); 
}


void ChunkViewEditorPanel::setSelectedScematic(Schematic* s) {
	m_selectedSchematic = s;
}

void ChunkViewEditorPanel::setupEvents() {
	auto mouseHandler = [this](Event* e) {
		MouseMovedEvent* mbe = (MouseMovedEvent*) e;

		int targetX = mbe->posx;
		int targetY = mbe->posy;

		ChunkRenderer::worldToGrid(targetX, targetY);

		if (mbe->left && m_selectedSchematic){
			m_chunk.schematic->placeSubcircuit(targetX, targetY, *m_selectedSchematic);
			m_selectedSchematic = nullptr;
			return;
		}


		if (mbe->right || mbe->left) {
			int resultComponent = mbe->right ? m_palettePanel.getRightBrush() : m_palettePanel.getLeftBrush();
			Paint(m_chunk, targetX, targetY, resultComponent);
		}
	};

	registerEventHandler(EventCode::M_MouseMove, mouseHandler);
	registerEventHandler(EventCode::M_LeftDown, mouseHandler);
	registerEventHandler(EventCode::M_RightDown, mouseHandler);
}

void ChunkViewEditorPanel::onImGuiDraw(){
	if (m_simulationManager.doAutotick()) {
		autoTickState++;
		if (autoTickState > m_simulationManager.getAutotickAmount()) {
			autoTickState = 0;
			m_chunk.tick();
		}
	}

	ChunkViewPanel::onImGuiDraw();
}