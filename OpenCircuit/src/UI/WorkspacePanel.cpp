#include "WorkspacePanel.h"

#include "../Workspace.h"

#include <imgui.h>

#include <fstream>

void WorkspacePanel::render(){
    const ImGuiWindowFlags menuBarFlags =
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize   |
        ImGuiWindowFlags_NoNav      |
        ImGuiWindowFlags_NoMove     |
        ImGuiWindowFlags_MenuBar;
    ImGui::Begin("Workspace", NULL, menuBarFlags);
    ImGui::Text("Schematics");

    if (ImGui::Button("Save")) {
        std::ofstream fs;
        fs.open("save.workspace");
        m_workspace.save(fs);
        fs.close();
    }
    ImGui::SameLine();
    if (ImGui::Button("Load")) {
        std::ifstream fs;
        fs.open("save.workspace");
        m_workspace.load(fs);
        fs.close();
    }

    if (ImGui::CollapsingHeader("New schematic")) {
        static char newSchematicName[20];
        ImGui::InputText("Name", newSchematicName, 20);
        if (ImGui::Button("Create")) {
            m_workspace.newSchematic(std::string(newSchematicName));
        }
    }

    if (ImGui::CollapsingHeader("Edit schematics")) {
        for (int i = m_workspace.schematicCount()-1; i >= 0; i--) {
            ImGui::PushID(i);
            if (ImGui::Button("^")) {
                m_workspace.moveUp(i);
            }
            ImGui::SameLine();
            ImGui::Text(m_workspace.getSchematic(i)->getName().c_str());
            ImGui::SameLine();

            if (ImGui::Button("Edit")) {
                m_workspace.setWorkingSchematic(i);
            }
            if (i > 0) {
                ImGui::SameLine();
                if (ImGui::Button("x")) {
                    m_workspace.deleteSchematic(i);
                }

            }
            //Subcircuits can only be placed in circuits *below* the current circuit
            if (i < m_workspace.getWorkingChunk()) {

                ImGui::SameLine();
                if (ImGui::Button("Place")) {
                    m_subcircuitPlacement = i;
                }
            }
            ImGui::PopID();
        }
    }
    ImGui::End();
}