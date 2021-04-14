#include <SFML/Graphics.hpp>

class Window {
public:
	Window(int x, int y);

	bool isOpen();
	void handleEvents();
	void beginDraw();
	void endDraw();
private:
	sf::RenderWindow _window;
};