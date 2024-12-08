#pragma once

class Event
{
public:
	int id;
	Event(int id);
};

class KeyEvent : public Event {
public:
	KeyEvent(int keyCode);
};

class MouseMovedEvent : public Event {
public:
    bool left; // If the left button is pressed
    bool right;  // If the right buutton is pressed

    bool isLeftDown; // If the left button is pressed down this frame
    bool isRightDown; // If the left button is pressed down this frame

    int posx, posy;

    MouseMovedEvent(int x, int y, bool l, bool r, bool ld, bool rd);
};

class Schematic;
struct SchematicChangedEvent : public Event {
    SchematicChangedEvent(Schematic* s);

    Schematic* changedSchematic;
};

struct SchematicPlaceEvent : public Event {
    SchematicPlaceEvent(Schematic* s);

    Schematic* placedSchematic;
};

enum EventCode
{
    //Key Down
    D_A = 0,        ///< The A key
    D_B,            ///< The B key
    D_C,            ///< The C key
    D_D,            ///< The D key
    D_E,            ///< The E key
    D_F,            ///< The F key
    D_G,            ///< The G key
    D_H,            ///< The H key
    D_I,            ///< The I key
    D_J,            ///< The J key
    D_K,            ///< The K key
    D_L,            ///< The L key
    D_M,            ///< The M key
    D_N,            ///< The N key
    D_O,            ///< The O key
    D_P,            ///< The P key
    D_Q,            ///< The Q key
    D_R,            ///< The R key
    D_S,            ///< The S key
    D_T,            ///< The T key
    D_U,            ///< The U key
    D_V,            ///< The V key
    D_W,            ///< The W key
    D_X,            ///< The X key
    D_Y,            ///< The Y key
    D_Z,            ///< The Z key
    D_Num0,         ///< The 0 key
    D_Num1,         ///< The 1 key
    D_Num2,         ///< The 2 key
    D_Num3,         ///< The 3 key
    D_Num4,         ///< The 4 key
    D_Num5,         ///< The 5 key
    D_Num6,         ///< The 6 key
    D_Num7,         ///< The 7 key
    D_Num8,         ///< The 8 key
    D_Num9,         ///< The 9 key
    D_Escape,       ///< The Escape key
    D_LControl,     ///< The left Control key
    D_LShift,       ///< The left Shift key
    D_LAlt,         ///< The left Alt key
    D_LSystem,      ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
    D_RControl,     ///< The right Control key
    D_RShift,       ///< The right Shift key
    D_RAlt,         ///< The right Alt key
    D_RSystem,      ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
    D_Menu,         ///< The Menu key
    D_LBracket,     ///< The [ key
    D_RBracket,     ///< The ] key
    D_Semicolon,    ///< The ; key
    D_Comma,        ///< The D_, key
    D_Period,       ///< The . key
    D_Quote,        ///< The ' key
    D_Slash,        ///< The / key
    D_Backslash,    ///< The \ key
    D_Tilde,        ///< The ~ key
    D_Equal,        ///< The = key
    D_Hyphen,       ///< The - key (hyphen)
    D_Space,        ///< The Space key
    D_Enter,        ///< The Enter/Return keys
    D_Backspace,    ///< The Backspace key
    D_Tab,          ///< The Tabulation key
    D_PageUp,       ///< The Page up key
    D_PageDown,     ///< The Page down key
    D_End,          ///< The End key
    D_Home,         ///< The Home key
    D_Insert,       ///< The Insert key
    D_Delete,       ///< The Delete key
    D_Add,          ///< The + key
    D_Subtract,     ///< The - key (minus, usually from numpad)
    D_Multiply,     ///< The * key
    D_Divide,       ///< The / key
    D_Left,         ///< Left arrow
    D_Right,        ///< Right arrow
    D_Up,           ///< Up arrow
    D_Down,         ///< Down arrow

    //Key up
    U_A = 100,        ///< The A key
    U_B,            ///< The B key
    U_C,            ///< The C key
    U_D,            ///< The D key
    U_E,            ///< The E key
    U_F,            ///< The F key
    U_G,            ///< The G key
    U_H,            ///< The H key
    U_I,            ///< The I key
    U_J,            ///< The J key
    U_K,            ///< The K key
    U_L,            ///< The L key
    U_M,            ///< The M key
    U_N,            ///< The N key
    U_O,            ///< The O key
    U_P,            ///< The P key
    U_Q,            ///< The Q key
    U_R,            ///< The R key
    U_S,            ///< The S key
    U_T,            ///< The T key
    U_U,            ///< The U key
    U_V,            ///< The V key
    U_W,            ///< The W key
    U_X,            ///< The X key
    U_Y,            ///< The Y key
    U_Z,            ///< The Z key
    U_Num0,         ///< The 0 key
    U_Num1,         ///< The 1 key
    U_Num2,         ///< The 2 key
    U_Num3,         ///< The 3 key
    U_Num4,         ///< The 4 key
    U_Num5,         ///< The 5 key
    U_Num6,         ///< The 6 key
    U_Num7,         ///< The 7 key
    U_Num8,         ///< The 8 key
    U_Num9,         ///< The 9 key
    U_Escape,       ///< The Escape key
    U_LControl,     ///< The left Control key
    U_LShift,       ///< The left Shift key
    U_LAlt,         ///< The left Alt key
    U_LSystem,      ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
    U_RControl,     ///< The right Control key
    U_RShift,       ///< The right Shift key
    U_RAlt,         ///< The right Alt key
    U_RSystem,      ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
    U_Menu,         ///< The Menu key
    U_LBracket,     ///< The [ key
    U_RBracket,     ///< The ] key
    U_Semicolon,    ///< The ; key
    U_Comma,        ///< The U_, key
    U_Period,       ///< The . key
    U_Quote,        ///< The ' key
    U_Slash,        ///< The / key
    U_Backslash,    ///< The \ key
    U_Tilde,        ///< The ~ key
    U_Equal,        ///< The = key
    U_Hyphen,       ///< The - key (hyphen)
    U_Space,        ///< The Space key
    U_Enter,        ///< The Enter/Return keys
    U_Backspace,    ///< The Backspace key
    U_Tab,          ///< The Tabulation key
    U_PageUp,       ///< The Page up key
    U_PageDown,     ///< The Page down key
    U_End,          ///< The End key
    U_Home,         ///< The Home key
    U_Insert,       ///< The Insert key
    U_Delete,       ///< The Delete key
    U_Add,          ///< The + key
    U_Subtract,     ///< The - key (minus, usually from numpad)
    U_Multiply,     ///< The * key
    U_Divide,       ///< The / key
    U_Left,         ///< Left arrow
    U_Right,        ///< Right arrow
    U_Up,           ///< Up arrow
    U_Down,         ///< Down arrow
    //---------------- Mouse Events --------------

    M_LeftDown = 200,
    M_RightDown,

    M_MouseMove,

    // ---------------- UI Events ----------------

    I_SchematicChanged = 300,
    I_SchematicPlaced,
    I_ChunkChanged
};