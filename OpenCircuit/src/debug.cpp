#ifdef DEBUG
#include "Debug.h"
#include "Workspace.h"
#include "Simulation/Chunk.h"
#include "Simulation/Subcircuit.h"
#include "Rendering/Window/window.h"
#include "Rendering/Renderers/ChunkRenderer.h"

void Debug::drawImGui(Workspace& workspace, Window& w) {
	ImGui::Begin("Debug");
	if (ImGui::CollapsingHeader("All Circuits")) {
		Chunk* c = workspace.getSchematic()->getChunk();
		for (auto it = c->subcircuits.begin(); it != c->subcircuits.end(); ++it) {
			if (ImGui::Button("Force render")) {
				ChunkRenderer::Render(w, (*it)->getSchematic().getChunk());
			}
		}
	}
	ImGui::End();
}

#endif