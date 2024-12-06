#include "ChunkViewPanel.h"
#include "../Simulation/Chunk.h"
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

		if (mbe->rightDown || mbe->leftDown) {
			int resultComponent = mbe->rightDown ? m_palettePanel.getRightBrush() : m_palettePanel.getLeftBrush();
			Paint(m_chunk, targetX, targetY, resultComponent);
		}
	};

	m_eventManager.addEventCallback(EventCode::M_MouseMove, mouseHandler);
	m_eventManager.addEventCallback(EventCode::M_LeftDown, mouseHandler);
	m_eventManager.addEventCallback(EventCode::M_RightDown, mouseHandler);
}

void ChunkViewPanel::render(){
	if(ImGui::Begin(m_chunk.schematic->getName().c_str())) {
		m_viewportSize = ImGui::GetWindowSize();;
		m_texture.create(m_viewportSize.x, m_viewportSize.y);
		m_texture.clear(sf::Color::Black);
		ChunkRenderer::Render(m_texture, &m_chunk);

		ImGui::ImageButton(m_texture, 0);
		handleInputs();
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