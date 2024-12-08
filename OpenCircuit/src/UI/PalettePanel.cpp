#include "PalettePanel.h"

#include "../Rendering/Renderers/ChunkRenderer.h"
#include "imgui.h"

// TODO: Do something much better than this
ImVec4 vec4ToImVec4(vec4<unsigned char> v4) {
	return ImVec4(v4.x / 255.0f, v4.y / 255.0f, v4.z / 255.0f, v4.w / 255.0f);
}

void PalettePanel::render(){
		ImGui::Begin("Palette");
		//Bad practice but whatever
		static char const* componentTooltips[7] = { "Nothing", "Wire", "Input", "Output", "Transistor", "Not", "Junction"};
		for (int i = 1; i < 7; i++) {
			ImGui::PushID(i);
			ImGui::SameLine();
			ImGui::PushStyleColor(ImGuiCol_Button, vec4ToImVec4(ChunkRenderer::getComponentColour(i)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, vec4ToImVec4(ChunkRenderer::getComponentColour(i)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, vec4ToImVec4(ChunkRenderer::getComponentColour(i)));
			if (ImGui::Button(" ", ImVec2(20, 20)))
				m_leftBrush = i;
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("%s", componentTooltips[i]);

			ImGui::PopStyleColor(3);
			ImGui::PopID();
		}
		ImGui::End();
}