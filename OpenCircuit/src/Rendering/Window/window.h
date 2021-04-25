#pragma once

#include "EventManager.h"

class Window {
public:
	virtual bool isOpen()=0;
	virtual void handleEvents()=0;

	virtual void beginDraw()=0;
	virtual void endDraw()=0;

	virtual void imGuiBegin()=0;
	virtual void imGuiDraw()=0;

	virtual void addEventCallback(int eventId, EventCallback ec)=0;

	virtual void screenToWorld(int &x, int &y)=0;

protected:
	EventManager _eManager;
};