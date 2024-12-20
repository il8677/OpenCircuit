#include "UIPanel.h"

#include <imgui.h>

void UIPanel::registerEventHandler(EventCode eventCode, EventCallback callback){
    m_eventManager.addEventCallback(eventCode, callback);
}

void UIPanel::render() {
	while(m_jobQueue.size()){
		m_jobQueue.front()();
		m_jobQueue.pop();
	}
    onImGuiDraw();

    for(auto it = m_children.begin(); it != m_children.end(); ++it){
		if((*it)->m_destroy){
			it = m_children.erase(it);
			it--;
			continue;
		}
        (*it)->render();
    }
}

void UIPanel::handleEvents() {
	// Handle events
	ImGuiIO& io = ImGui::GetIO();
	bool isHovered = ImGui::IsItemHovered();
	bool isFocused = ImGui::IsItemFocused();
	ImVec2 mousePositionAbsolute = ImGui::GetMousePos();
	ImVec2 screenPositionAbsolute = ImGui::GetItemRectMin();
	ImVec2 mousePositionRelative = ImVec2(mousePositionAbsolute.x - screenPositionAbsolute.x, mousePositionAbsolute.y - screenPositionAbsolute.y);

	if(isHovered){
		m_eventManager.handleEvent(new MouseMovedEvent(mousePositionRelative.x, mousePositionRelative.y, ImGui::IsMouseDown(ImGuiMouseButton_Left), ImGui::IsMouseDown(ImGuiMouseButton_Right), ImGui::IsMouseClicked(ImGuiMouseButton_Left), ImGui::IsMouseClicked(ImGuiMouseButton_Right)));
	}
}

void UIPanel::dispatchEvent(Event* e) { 
	m_eventManager.handleEventPassthrough(e); 

	for(auto& child : m_children) {
		child->dispatchEvent(e);
	}
}
