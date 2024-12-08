#include "SimulationManager.h"

#include <imgui.h>
#include <vector>

#include "../Workspace.h"

void SimulationManager::onImGuiDraw(){
    ImGui::Begin("Simulation Manager");
    if (ImGui::CollapsingHeader("Inputs")) {
        std::vector<char*> inputs = m_workspace.getChunk()->getInputs();
        for (int i = 0; i < inputs.size(); i++) {
            ImGui::PushID(i);
            if (i > 0)
                ImGui::SameLine();
            if (ImGui::Checkbox(" ", (bool*)inputs[i])) {
                m_workspace.getChunk()->updateInputs();
            }
            ImGui::PopID();
        }
    }
    if (ImGui::CollapsingHeader("Outputs")) {

        std::vector<char*> outputs = m_workspace.getChunk()->getOutputs();
        for (int i = 0; i < outputs.size(); i++) {
            if (i > 0)
                ImGui::SameLine();
            ImGui::Text("%d", *outputs[i]);
        }
    }
    if (ImGui::CollapsingHeader("Controls")) {
        if (ImGui::Button("Reset")) {
            m_workspace.getChunk()->reset();
        }
        if (ImGui::Button("Tick")) {
            m_workspace.getChunk()->tick();
        }

        ImGui::Text("Autotick");
        ImGui::SliderInt("Tick period", &m_autoTickAmount, 1, 100);
        ImGui::Checkbox("Do autotick", &m_doAutotick);
    }
    ImGui::End();
}