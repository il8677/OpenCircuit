#include "ValidationPanel.h"
#include <Validation/Validator.h>
#include <Simulation/Chunk.h>
#include <imgui.h>
#include <imgui_stdlib.h>

ValidationPanel::ValidationPanel(Chunk& c) : m_activeChunk(c) { // TODO, hook up to event system instead of passing chunk

}

void ValidationPanel::onImGuiDraw() {
	ImGui::Begin("Validator");

	ValidationSet& set = m_activeChunk.schematic->getValidationSet();
	if(ImGui::SmallButton("+")) {
		set.addTestCase();
	}

	for(size_t j = 0; j < set.getTestCaseCount(); j++) {
		TestCase& tc = set.getTestCase(j);
		if(ImGui::TreeNode(std::to_string(j).c_str())){
			m_selectedCase = j;
			ImGui::TreePop();
		}
	}

	if(m_selectedCase != -1) {
		TestCaseTransformer& transformer = set.getTransformer();
		TestCase& tc =  set.getTestCase(m_selectedCase);

		int lineCounts[2] = { transformer.getInputLines(), transformer.getOutputLines() };

		ImGui::PushItemWidth(40);
		if(ImGui::InputInt2("Lines", lineCounts, ImGuiInputTextFlags_CharsDecimal)) {
			transformer.setInputLines(lineCounts[0]);
			transformer.setOutputLines(lineCounts[1]);
		}
		ImGui::PopItemWidth();

		ImGui::PushItemWidth(80);
		ImGui::InputInt("Tick requirement", &set.tickRequirement);
		ImGui::PopItemWidth();

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

		ImGui::InputTextMultiline("Input", &tc.input);
		ImGui::InputTextMultiline("Output", &tc.expectedOutput);

		if(ImGui::Button("Run set")) {
			Validator validator;
			std::vector<bool> results = validator.validate(set, m_activeChunk);
			m_latestResult.clear();
			for(bool res : results) m_latestResult.push_back(res ? '1' : '0');
		}	
	}
	if(m_latestResult.size()) {
		ImGui::Text("%s", m_latestResult.data());
	}
	ImGui::End();
}
