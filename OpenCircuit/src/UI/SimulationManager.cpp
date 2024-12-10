#include "SimulationManager.h"

#include <imgui.h>
#include <vector>

#include "../Workspace.h"

void SimulationManager::onImGuiDraw(){
    ImGui::Begin("Simulation Manager");
    ImGui::SeparatorText("Inputs");
    std::vector<char*> inputs = m_chunk.getInputs();
    for (int i = 0; i < inputs.size(); i++) {
        ImGui::PushID(i);
        if (i > 0)
            ImGui::SameLine();
        if (ImGui::Checkbox(" ", (bool*)inputs[i])) {
            m_chunk.updateInputs();
        }
        ImGui::PopID();
    }

    ImGui::SeparatorText("Outputs");
    std::vector<char*> outputs = m_chunk.getOutputs();
    for (int i = 0; i < outputs.size(); i++) {
        if (i > 0)
            ImGui::SameLine();
        ImGui::Text("%d", *outputs[i]);
    }

    ImGui::SeparatorText("Controls");
    if (ImGui::Button("Reset")) {
        m_chunk.reset();
    }
    if (ImGui::Button("Tick")) {
        m_chunk.tick();
    }

    ImGui::Text("Autotick");
    ImGui::SliderInt("Tick period", &m_autoTickAmount, 1, 100);
    ImGui::Checkbox("Do autotick", &m_doAutotick);
    ImGui::End();
}