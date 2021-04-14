#include "Event.h"

Event::Event(int id) : id(id) {};

KeyEvent::KeyEvent(int keyCode) : Event(keyCode) {

}

MouseMovedEvent::MouseMovedEvent(int x, int y) : posx(x), posy(y), Event(EventCode::MouseMove) {};

MouseButtonEvent::MouseButtonEvent(int x, int y, int id) : posx(x), posy(y), Event(id) {}