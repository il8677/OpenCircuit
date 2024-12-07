#include "Event.h"

#include "SFMLWindow.h"
#include <imgui.h>
#include <imgui-SFML.h>

bool SFMLWindow::isOpen() {
	return _window.isOpen();
}

void SFMLWindow::screenToWorld(int& x, int& y) {

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
			_eManager.handleEvent(new MouseMovedEvent(e.mouseMove.x, e.mouseMove.y, sf::Mouse::isButtonPressed(sf::Mouse::Left), sf::Mouse::isButtonPressed(sf::Mouse::Right), false, false));
		}
		else if (e.type == sf::Event::MouseButtonPressed) {
            bool left = false;
            bool right = false;

			switch (e.mouseButton.button) {
			case sf::Mouse::Right:
                right = true;
				break;
			case sf::Mouse::Left:
                left = true;
				break;
			default:
				continue;
			}
			_eManager.handleEvent(new MouseMovedEvent(e.mouseButton.x, e.mouseButton.y,sf::Mouse::isButtonPressed(sf::Mouse::Left), sf::Mouse::isButtonPressed(sf::Mouse::Right), left, right));
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
    auto& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    
	_window.resetGLStates();
	_deltaClock.restart();

}