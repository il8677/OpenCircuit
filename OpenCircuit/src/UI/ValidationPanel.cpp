#include "ValidationPanel.h"

#include <imgui.h>

ValidationPanel::ValidationPanel() {

}

void ValidationPanel::onImGuiDraw() {
	ImGui::Begin("Validator");

	const bool rootExpanded = ImGui::TreeNodeEx("Sets", ImGuiTreeNodeFlags_AllowItemOverlap);
	ImGui::SameLine();
	if(ImGui::SmallButton("+")){
		ImGui::OpenPopup("Set Name");
	}
	
	if(ImGui::BeginPopupModal("Set Name")){
		ImGui::SetWindowSize({125, 55});
		static char nameBuf[1024] = {};
		ImGui::PushItemWidth(110);
		ImGui::SetKeyboardFocusHere();
		if(ImGui::InputText("##setnameinput", nameBuf, 1024, ImGuiInputTextFlags_EnterReturnsTrue)){
			if(nameBuf[0] != '\0') m_sets.emplace_back(nameBuf);
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	if(rootExpanded){
		for(size_t i = 0; i < m_sets.size(); i++) {
			ValidationSet& set = m_sets[i];
			const bool setExpanded = ImGui::TreeNodeEx(set.getName().c_str(), ImGuiTreeNodeFlags_AllowItemOverlap);
			ImGui::SameLine();
			if(ImGui::SmallButton("+")) {
				set.addTestCase();
			}

			if(setExpanded){
				for(size_t j = 0; j < set.getTestCaseCount(); j++) {
					TestCase& tc = set.getTestCase(j);
					if(ImGui::TreeNode(std::to_string(j).c_str())){
						m_selectedSet = i;
						m_selectedCase = j;
						ImGui::TreePop();
					}
				}
				ImGui::TreePop();
			}
		}
		ImGui::TreePop();
	}


	if(m_selectedCase != -1) {
		ValidationSet& set = m_sets[m_selectedSet];
		TestCaseTransformer& transformer = set.getTransformer();
		TestCase& tc =  set.getTestCase(m_selectedCase);

		int lineCounts[2] = { transformer.getInputLines(), transformer.getOutputLines() };
		int ioCounts[2] = { transformer.getInputCount(), transformer.getOutputCount() };

		if(ImGui::InputInt2("Lines", lineCounts)) {
			transformer.setInputLines(lineCounts[0]);
			transformer.setOutputLines(lineCounts[1]);
		}

		if(ImGui::InputInt2("IO", ioCounts)) {
			transformer.setInputCount(ioCounts[0]);
			transformer.setOutputCount(ioCounts[1]);
		}

		for(int y = 0; y < transformer.getInputLines(); y++) {
			for(int x = 0; x < transformer.getInputCount(); x++) {
				if(x > 0) ImGui::SameLine();
				ImGui::PushID(y * transformer.getInputCount() + x);
				if(ImGui::Selectable("O", transformer.getInputMapping(x) == y, 0, {10, 10})){
					transformer.setInputMapping(x, y);
				}
				ImGui::PopID();
			}
		}

		tc.input.reserve(1024);
		tc.expectedOutput.reserve(1024);

		ImGui::InputTextMultiline("Input", tc.input.data(), 1024);
		ImGui::InputTextMultiline("Output", tc.expectedOutput.data(), 1024);
	}

	ImGui::End();
}
