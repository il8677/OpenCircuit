#include "Event.h"

Event::Event(int id) : id(id) {};

KeyEvent::KeyEvent(int keyCode) : Event(keyCode) {}

MouseMovedEvent::MouseMovedEvent(int x, int y, bool ld, bool rd) : posx(x), posy(y), Event(EventCode::M_MouseMove), leftDown(ld), rightDown(rd) {};

MouseButtonEvent::MouseButtonEvent(int x, int y, int id) : posx(x), posy(y), Event(id) {}