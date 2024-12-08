#include "WorkspacePanel.h"

#include "../Workspace.h"

#include <imgui.h>

#include <fstream>

void WorkspacePanel::onImGuiDraw(){
    const ImGuiWindowFlags menuBarFlags=0;
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
        for (int i = 0; i < m_workspace.schematicCount(); i++) {
            ImGui::PushID(i);
            if (ImGui::Button("v")) {
                m_workspace.moveUp(i);
            }
            ImGui::SameLine();
            ImGui::Text("%s", m_workspace.getSchematic(i)->getName().c_str());
            ImGui::SameLine();

            if (ImGui::Button("Edit")) {
                auto e = SchematicChangedEvent(m_workspace.getSchematic(i));
                dispatchEvent(&e);
            }
            if (i > 0) {
                ImGui::SameLine();
                if (ImGui::Button("x")) {
                    m_workspace.deleteSchematic(i);
                }

            }
            //Subcircuits can only be placed in circuits *below* the current circuit
            // At some point the UI should enforce that
            ImGui::SameLine();
            if (ImGui::Button("Place")) {
                auto e = SchematicPlaceEvent(m_workspace.getSchematic(i));
                dispatchEvent(&e);
            }
            ImGui::PopID();
        }
    }
    ImGui::End();
}