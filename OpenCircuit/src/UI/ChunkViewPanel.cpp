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

void ChunkViewPanel::setupEvents() {
	auto mouseHandler = [this](Event* e) {
		MouseMovedEvent* mbe = (MouseMovedEvent*) e;

		int targetX = mbe->posx;
		int targetY = mbe->posy;

		ChunkRenderer::worldToGrid(targetX, targetY);

		if (mbe->leftDown && m_workspacePanel.hasSelectedSubcircuit()){
			Schematic& s = *m_workspace.getSchematic(m_workspacePanel.popSelectedSubcircuit());
			m_chunk.schematic->placeSubcircuit(targetX, targetY, s);
			return;
		}

		if(mbe->leftDown){
			if(m_chunk.schematic->getCellId(targetX, targetY) == 999){
				SubcircuitProxy* proxy = reinterpret_cast<SubcircuitProxy*>(m_chunk.schematic->getComponent(targetX, targetY));
				m_popupChunk = &m_chunk.getSubcircuitFromProxy(proxy).getChunk();
                return;
			}
		}

		if (mbe->rightDown || mbe->leftDown) {
            m_popupChunk = nullptr;
			int resultComponent = mbe->rightDown ? m_palettePanel.getRightBrush() : m_palettePanel.getLeftBrush();
			Paint(m_chunk, targetX, targetY, resultComponent);
		}
	};

	m_eventManager.addEventCallback(EventCode::M_MouseMove, mouseHandler);
	m_eventManager.addEventCallback(EventCode::M_LeftDown, mouseHandler);
	m_eventManager.addEventCallback(EventCode::M_RightDown, mouseHandler);
}

void ChunkViewPanel::render(){
	bool enabled = ImGui::Begin(m_chunk.schematic->getName().c_str());

    if(!enabled){
        ImGui::End();
        return;
    }

    m_viewportSize = ImGui::GetWindowSize();;
    m_texture.create(m_viewportSize.x, m_viewportSize.y);
    m_texture.clear(sf::Color::Black);
    ChunkRenderer::Render(m_texture, &m_chunk);

    ImGui::ImageButton(m_texture, 0);
    handleInputs();


    if(m_popupChunk){
        const char* popupName = m_popupChunk->schematic->getName().c_str();
        ImGui::OpenPopup(popupName);
        if(ImGui::BeginPopup(popupName)){
            m_popupTexture.create(m_viewportSize.x/4, m_viewportSize.y/4);
            m_popupTexture.clear(sf::Color::Black);
            ChunkRenderer::Render(m_popupTexture, m_popupChunk, true);

            ImGui::ImageButton(m_popupTexture, 0);
            ImGui::EndPopup();
        }
    }
	ImGui::End();

}

void ChunkViewPanel::handleInputs() {
	// Handle events
	ImGuiIO& io = ImGui::GetIO();
	bool isHovered = ImGui::IsItemHovered();
	bool isFocused = ImGui::IsItemFocused();
	ImVec2 mousePositionAbsolute = ImGui::GetMousePos();
	ImVec2 screenPositionAbsolute = ImGui::GetItemRectMin();
	ImVec2 mousePositionRelative = ImVec2(mousePositionAbsolute.x - screenPositionAbsolute.x, mousePositionAbsolute.y - screenPositionAbsolute.y);

	if(isHovered && isFocused){
		m_eventManager.handleEvent(new MouseMovedEvent(mousePositionRelative.x, mousePositionRelative.y, ImGui::IsMouseDown(ImGuiMouseButton_Left), ImGui::IsMouseDown(ImGuiMouseButton_Right)));
	}
}