#pragma once
#include "Window.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class SFMLWindow : public Window {
	sf::RenderWindow _window;
	sf::Clock _deltaClock;
public:
	SFMLWindow(int x, int y);
	~SFMLWindow();

	bool isOpen() override;
	void handleEvents() override;

	void beginDraw() override;
	void endDraw() override;

	void imGuiBegin() override;
	void imGuiDraw() override;

	void addEventCallback(int eventId, EventCallback ec) override;

	void screenToWorld(int& x, int& y) override;

	void renderVerts(sf::VertexArray va);
};