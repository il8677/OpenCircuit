#include "window.h"

bool Window::isOpen() {
	return _window.isOpen();
}

void Window::handleEvents()
{
	sf::Event e;

	while (_window.pollEvent(e)) {

		if (e.type == sf::Event::Closed)
			_window.close();
	}
}

void Window::beginDraw()
{
	_window.clear(sf::Color::Black);
}

void Window::endDraw()
{
	_window.display();
}

Window::Window(int x, int y) : _window(sf::VideoMode(x, y), "OpenCircuit")
{
	
}