#include "Event.h"

Event::Event(int id) : id(id) {};

KeyEvent::KeyEvent(int keyCode) : Event(keyCode) {}

MouseMovedEvent::MouseMovedEvent(int x, int y, bool l, bool r, bool ld, bool rd) : posx(x), posy(y), Event(EventCode::M_MouseMove), left(l), right(r), isLeftDown(ld), isRightDown(rd) {};

SchematicChangedEvent::SchematicChangedEvent(Schematic* s) : Event(I_SchematicChanged), changedSchematic(s) {

}

SchematicPlaceEvent::SchematicPlaceEvent(Schematic* s) : Event(I_SchematicPlaced), placedSchematic(s) {

}