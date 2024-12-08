#include "EventManager.h"

void EventManager::addEventCallback(int eventId, EventCallback ec) {
	if (eventCallbacks.find(eventId) == eventCallbacks.end()) {
		eventCallbacks[eventId] = std::vector<EventCallback>();
	}
	eventCallbacks[eventId].push_back(ec);
}

void EventManager::handleEvent(Event* event) {
	handleEventPassthrough(event);
	delete event;
}


void EventManager::handleEventPassthrough(Event* event) {
	for (int i = 0; i < eventCallbacks[event->id].size(); i++) {
		eventCallbacks[event->id][i](event);
	}
}