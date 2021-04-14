#include "window.h"
#include <imgui.h>
#include <imgui-SFML.h>
#include "Event.h"

bool Window::isOpen() {
	return _window.isOpen();
}

void Window::handleEvents()
{
	sf::Event e;

	while (_window.pollEvent(e)) {

		ImGui::SFML::ProcessEvent(e);
		if (e.type == sf::Event::Closed)
			_window.close();
		else if (e.type == sf::Event::KeyPressed) {
			_eManager.handleEvent(new KeyEvent(e.key.code));
		}
		else if (e.type == sf::Event::MouseMoved) {
			_eManager.handleEvent(new MouseMovedEvent(e.mouseMove.x, e.mouseMove.y));
		}
		else if (e.type == sf::Event::MouseButtonPressed) {
			int id;

			switch (e.mouseButton.button) {
			case sf::Mouse::Right:
				id = EventCode::RightDown;
				break;
			case sf::Mouse::Left:
				id = EventCode::LeftDown;
				break;
			}
			_eManager.handleEvent(new MouseButtonEvent(e.mouseButton.x, e.mouseButton.y, id));
		}
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

void Window::imGuiBegin() {
	ImGui::SFML::Update(_window, _deltaClock.restart());
}

void Window::imGuiDraw() {
	ImGui::SFML::Render(_window);
}

void Window::renderVerts(sf::VertexArray va)
{
	_window.draw(va);
}

void Window::addEventCallback(int eventId, EventCallback ec)
{
	_eManager.addEventCallback(eventId, ec);
}

Window::~Window() {
	ImGui::SFML::Shutdown();
}

Window::Window(int x, int y) : _window(sf::VideoMode(x, y), "OpenCircuit")
{
	_window.setVerticalSyncEnabled(true);
	
	ImGui::SFML::Init(_window);
	_window.resetGLStates();
	_deltaClock.restart();

}