#include "Event.h"

#include "SFMLWindow.h"
#include <imgui.h>
#include <imgui-SFML.h>

bool SFMLWindow::isOpen() {
	return _window.isOpen();
}

void SFMLWindow::screenToWorld(int& x, int& y) {

}

void SFMLWindow::renderVerts(sf::VertexArray va)
{
	_window.draw(va);
}

void SFMLWindow::handleEvents()
{
	sf::Event e;

	while (_window.pollEvent(e)) {

		ImGui::SFML::ProcessEvent(e);
		if (e.type == sf::Event::Closed)
			_window.close();
		else if (e.type == sf::Event::KeyPressed) {
			if(e.key.code <= 74)
				_eManager.handleEvent(new KeyEvent(e.key.code));
		}
		else if (e.type == sf::Event::KeyReleased) {
			if (e.key.code <= 74)
				_eManager.handleEvent(new KeyEvent(e.key.code + 100));
		}
		else if (e.type == sf::Event::MouseMoved) {
			_eManager.handleEvent(new MouseMovedEvent(e.mouseMove.x, e.mouseMove.y, sf::Mouse::isButtonPressed(sf::Mouse::Left), sf::Mouse::isButtonPressed(sf::Mouse::Right)));
		}
		else if (e.type == sf::Event::MouseButtonPressed) {
			int id;

			switch (e.mouseButton.button) {
			case sf::Mouse::Right:
				id = EventCode::M_RightDown;
				break;
			case sf::Mouse::Left:
				id = EventCode::M_LeftDown;
				break;
			default:
				continue;
			}
			_eManager.handleEvent(new MouseButtonEvent(e.mouseButton.x, e.mouseButton.y, id));
		}
	}
}

void SFMLWindow::beginDraw()
{
	_window.clear(sf::Color::Black);
}

void SFMLWindow::endDraw()
{
	_window.display();
}

void SFMLWindow::imGuiBegin() {
	ImGui::SFML::Update(_window, _deltaClock.restart());
}

void SFMLWindow::imGuiDraw() {
	ImGui::SFML::Render(_window);
}

void SFMLWindow::addEventCallback(int eventId, EventCallback ec)
{
	_eManager.addEventCallback(eventId, ec);
}

SFMLWindow::~SFMLWindow() {
	ImGui::SFML::Shutdown();
}

SFMLWindow::SFMLWindow(int x, int y) : _window(sf::VideoMode(x, y), "OpenCircuit")
{
	_window.setVerticalSyncEnabled(true);
	
	ImGui::SFML::Init(_window);
	_window.resetGLStates();
	_deltaClock.restart();

}