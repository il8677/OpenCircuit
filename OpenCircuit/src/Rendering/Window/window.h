#include <SFML/Graphics.hpp>

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
private:
	sf::RenderWindow _window;
	sf::Clock _deltaClock;
};