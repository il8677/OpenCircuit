#include "ChunkViewPanel.h"
#include "../Simulation/Chunk.h"
#include "../Simulation/Schematic.h"
#include "../Simulation/Subcircuit.h"
#include "../Rendering/Renderers/ChunkRenderer.h"

#include "PalettePanel.h"
#include "WorkspacePanel.h"
#include "../Workspace.h"

#include <imgui.h>
#include <imgui-SFML.h>

void Paint(Chunk& c, int targetX, int targetY, int resultComponent){
	if (c.schematic->getCellId(targetX, targetY) != 999)
		c.schematic->setComponent(resultComponent, targetX, targetY);
	else if (resultComponent == 0)
		c.schematic->deleteSubcircuit(targetX, targetY);
}

ChunkViewPanel::ChunkViewPanel(Chunk& chunk, PalettePanel& palettePanel) : 
	m_chunk(chunk), m_palettePanel(palettePanel) { 

	setupEvents(); 
}


void ChunkViewPanel::setSchematic(Schematic* s) {
    m_chunk = Chunk(s);
}

void ChunkViewPanel::setSelectedScematic(Schematic* s) {
	m_selectedSchematic = s;
}

void ChunkViewPanel::setupEvents() {
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

		if(mbe->isLeftDown){
			if(m_chunk.schematic->getCellId(targetX, targetY) == 999){
				SubcircuitProxy* proxy = reinterpret_cast<SubcircuitProxy*>(m_chunk.schematic->getComponent(targetX, targetY));
				m_popupChunk = &m_chunk.getSubcircuitFromProxy(proxy).getChunk();
                ImGui::OpenPopup("PopupChunk");
                return;
			}
		}

		if (mbe->right || mbe->left) {
            m_popupChunk = nullptr;
			int resultComponent = mbe->right ? m_palettePanel.getRightBrush() : m_palettePanel.getLeftBrush();
			Paint(m_chunk, targetX, targetY, resultComponent);
		}
	};

	registerEventHandler(EventCode::M_MouseMove, mouseHandler);
	registerEventHandler(EventCode::M_LeftDown, mouseHandler);
	registerEventHandler(EventCode::M_RightDown, mouseHandler);
}

void ChunkViewPanel::onImGuiDraw(){
	bool enabled = ImGui::Begin("Editor");

    if(!enabled){
        ImGui::End();
        return;
    }

    m_viewportSize = ImGui::GetWindowSize();;
    m_texture.create(m_viewportSize.x, m_viewportSize.y);
    m_texture.clear(sf::Color::Black);
    ChunkRenderer::Render(m_texture, &m_chunk);

    ImGui::ImageButton(m_texture, 0);
    handleEvents();

    if(ImGui::BeginPopup("PopupChunk")){
        m_popupTexture.create(m_viewportSize.x/4, m_viewportSize.y/4);
        m_popupTexture.clear(sf::Color::Black);
        ChunkRenderer::Render(m_popupTexture, m_popupChunk, true);

        ImGui::ImageButton(m_popupTexture, 0);
        ImGui::EndPopup();
    }
	ImGui::End();

}