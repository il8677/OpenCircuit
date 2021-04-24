#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "EventManager.h"

// TODO: Abstract from SFML

class Window {
public:
	Window(int x, int y);
	~Window();

	bool isOpen();
	void handleEvents();

	void beginDraw();
	void endDraw();

	void imGuiBegin();
	void imGuiDraw();

	void renderVerts(sf::VertexArray va);

	void addEventCallback(int eventId, EventCallback ec);

	void screenToWorld(int &x, int &y);

private:
	EventManager _eManager;

	sf::RenderWindow _window;
	sf::Clock _deltaClock;
};