#pragma once
#include <SFML/Graphics.hpp>

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
private:
	sf::RenderWindow _window;
	sf::Clock _deltaClock;
};