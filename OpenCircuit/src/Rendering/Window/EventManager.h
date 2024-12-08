#pragma once
#include <map>
#include <vector>
#include <functional>

#include "Event.h"

typedef std::function<void(Event*)> EventCallback;


class EventManager
{
	std::map<int, std::vector<EventCallback>> eventCallbacks;

public:
	void addEventCallback(int eventId, EventCallback ec);

	void handleEvent(Event* event);
	void handleEventPassthrough(Event* event);
};