#include "ChunkViewPanel.h"
#include "../Simulation/Chunk.h"
#include "../Simulation/Subcircuit.h"
#include "../Rendering/Renderers/ChunkRenderer.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui-SFML.h>

ChunkViewPanel::ChunkViewPanel(Chunk& chunk) : m_chunk(chunk) {
	registerEventHandler(EventCode::M_MouseMove, [&](Event* e){
		MouseMovedEvent* mbe = (MouseMovedEvent*) e;

		int targetX = mbe->posx;
		int targetY = mbe->posy;

        ChunkRenderer::worldToGrid(targetX, targetY);

        if(mbe->left){
            if(m_chunk.schematic->getCellId(targetX, targetY) == 999){
                SubcircuitProxy* proxy = reinterpret_cast<SubcircuitProxy*>(m_chunk.schematic->getComponent(targetX, targetY));
                m_popupChunk = &m_chunk.getSubcircuitFromProxy(proxy).getChunk();
                ImGui::OpenPopup("PopupChunk");
                return;
            }
            m_popupChunk = nullptr;
        }
	});
}

void ChunkViewPanel::setSchematic(Schematic* s) {
    auto e = Event(I_ChunkChanged);
    dispatchEvent(&e);
    m_chunk = Chunk(s);
}

void ChunkViewPanel::onImGuiDraw(){
	bool enabled = ImGui::Begin(m_chunk.schematic->getName().c_str());

    if(!enabled){
        ImGui::End();
        return;
    }

    m_viewportSize = ImGui::GetWindowSize();;
    m_texture.create(m_viewportSize.x, m_viewportSize.y);
    m_texture.clear(sf::Color::Black);
    ChunkRenderer::Render(m_texture, &m_chunk, m_clipView);

    ImGui::ImageButton(m_texture, 0);
    handleEvents();

    if(ImGui::BeginPopup("PopupChunk")){
        if(ImGui::Button("Pin")) {
            const ImGuiWindow* window = ImGui::GetCurrentWindow();
            auto windowPos = window->Pos;
            auto windowSize = window->SizeFull;

            ChunkViewPanel& child = emplaceChild<ChunkViewPanel, Chunk&>(*m_popupChunk);
            child.setClipView(true);

            child.registerEventHandler(I_ChunkChanged, [&](Event*) {
                   child.destroy(); 
            });
            child.addJob([=](){
                ImGui::SetNextWindowPos(windowPos);
                ImGui::SetNextWindowSize(windowSize);
            });

            ImGui::CloseCurrentPopup();
        }
        m_popupTexture.create(m_viewportSize.x/4, m_viewportSize.y/4);
        m_popupTexture.clear(sf::Color::Black);
        ChunkRenderer::Render(m_popupTexture, m_popupChunk, true);

        ImGui::ImageButton(m_popupTexture, 0);
        ImGui::EndPopup();
    }
	ImGui::End();

}