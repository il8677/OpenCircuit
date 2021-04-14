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
    int posx, posy;
    MouseMovedEvent(int x, int y);
};

class MouseButtonEvent : public Event {
public:
    int posx, posy;
    MouseButtonEvent(int x, int y, int id);
};

enum EventCode
{
    A = 0,        ///< The A key
    B,            ///< The B key
    C,            ///< The C key
    D,            ///< The D key
    E,            ///< The E key
    F,            ///< The F key
    G,            ///< The G key
    H,            ///< The H key
    I,            ///< The I key
    J,            ///< The J key
    K,            ///< The K key
    L,            ///< The L key
    M,            ///< The M key
    N,            ///< The N key
    O,            ///< The O key
    P,            ///< The P key
    Q,            ///< The Q key
    R,            ///< The R key
    S,            ///< The S key
    T,            ///< The T key
    U,            ///< The U key
    V,            ///< The V key
    W,            ///< The W key
    X,            ///< The X key
    Y,            ///< The Y key
    Z,            ///< The Z key
    Num0,         ///< The 0 key
    Num1,         ///< The 1 key
    Num2,         ///< The 2 key
    Num3,         ///< The 3 key
    Num4,         ///< The 4 key
    Num5,         ///< The 5 key
    Num6,         ///< The 6 key
    Num7,         ///< The 7 key
    Num8,         ///< The 8 key
    Num9,         ///< The 9 key
    Escape,       ///< The Escape key
    LControl,     ///< The left Control key
    LShift,       ///< The left Shift key
    LAlt,         ///< The left Alt key
    LSystem,      ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
    RControl,     ///< The right Control key
    RShift,       ///< The right Shift key
    RAlt,         ///< The right Alt key
    RSystem,      ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
    Menu,         ///< The Menu key
    LBracket,     ///< The [ key
    RBracket,     ///< The ] key
    Semicolon,    ///< The ; key
    Comma,        ///< The , key
    Period,       ///< The . key
    Quote,        ///< The ' key
    Slash,        ///< The / key
    Backslash,    ///< The \ key
    Tilde,        ///< The ~ key
    Equal,        ///< The = key
    Hyphen,       ///< The - key (hyphen)
    Space,        ///< The Space key
    Enter,        ///< The Enter/Return keys
    Backspace,    ///< The Backspace key
    Tab,          ///< The Tabulation key
    PageUp,       ///< The Page up key
    PageDown,     ///< The Page down key
    End,          ///< The End key
    Home,         ///< The Home key
    Insert,       ///< The Insert key
    Delete,       ///< The Delete key
    Add,          ///< The + key
    Subtract,     ///< The - key (minus, usually from numpad)
    Multiply,     ///< The * key
    Divide,       ///< The / key
    Left,         ///< Left arrow
    Right,        ///< Right arrow
    Up,           ///< Up arrow
    Down,         ///< Down arrow

    //---------------- Mouse Events --------------

    LeftDown = 100,
    RightDown,

    MouseMove
};