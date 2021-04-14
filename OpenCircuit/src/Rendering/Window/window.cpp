#include "window.h"
#include <imgui.h>
#include <imgui-SFML.h>

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