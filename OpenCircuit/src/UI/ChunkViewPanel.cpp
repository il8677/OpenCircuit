#include "ChunkViewPanel.h"
#include "../Simulation/Chunk.h"
#include "../Rendering/Renderers/ChunkRenderer.h"

#include <imgui.h>
#include <imgui-SFML.h>

void ChunkViewPanel::render(){
	if(ImGui::Begin(m_chunk.schematic->getName().c_str())) {
		m_viewportSize = ImGui::GetWindowSize();;
		m_texture.create(m_viewportSize.x, m_viewportSize.y);
		m_texture.clear(sf::Color::Black);
		ChunkRenderer::Render(m_texture, &m_chunk);
		ImGui::Image(m_texture);
		ImGui::End();
	}
}