#pragma once

#include "Event.hpp"

namespace zui {

enum class KeyCode : std::uint16_t {
    A = 65,
    B = 66,
    C = 67,
    D = 68,
    E = 69,
    F = 70,
    G = 71,
    H = 72,
    I = 73,
    J = 74,
    K = 75,
    L = 76,
    M = 77,
    N = 78,
    O = 79,
    P = 80,
    Q = 81,
    R = 82,
    S = 83,
    T = 84,
    U = 85,
    V = 86,
    W = 87,
    X = 88,
    Y = 89,
    Z = 90,

    K_0 = 48,
    K_1 = 49,
    K_2 = 50,
    K_3 = 51,
    K_4 = 52,
    K_5 = 53,
    K_6 = 54,
    K_7 = 55,
    K_8 = 56,
    K_9 = 57,

    UP = 265,
    DOWN = 264,
    LEFT = 263,
    RIGHT = 262,

    SPACE = 32,
    ENTER = 257,
    ESCAPE = 256,
    BACKSPACE = 259,
    TAB = 258,
    LEFT_SHIFT = 340,
    RIGHT_SHIFT = 344,
    LEFT_CTRL = 341,
    RIGHT_CTRL = 345,
    LEFT_ALT = 342,
    RIGHT_ALT = 346,

    COMMA = 44,
    PERIOD = 46,
    SLASH = 47,
    SEMICOLON = 59,
    APOSTROPHE = 39,
    LEFT_BRACKET = 91,
    RIGHT_BRACKET = 93,
    BACKSLASH = 92,
    GRAVE = 96,
    EQUAL = 61,
    MINUS = 45,

    F2 = 291,
    F3 = 292,
    F4 = 293,
    F1 = 290,
    F5 = 294,
    F6 = 295,
    F7 = 296,
    F8 = 297,
    F9 = 298,
    F10 = 299,
    F11 = 300,
    F12 = 301,

    PAUSE = 284,
    INSERT = 260,
    HOME = 268,
    PAGE_UP = 266,
    DELETE = 261,
    END = 269,
    PAGE_DOWN = 270,
};

class KeyEvent : public Event {
public:
    inline KeyCode GetKeyCode() const { return m_keyCode; }

protected:
    KeyEvent(int keyCode) : m_keyCode(static_cast<KeyCode>(keyCode)) {}

    KeyCode m_keyCode;
};

class KeyPressedEvent : public KeyEvent {
public:
    KeyPressedEvent(int keyCode, bool isRepeat) : KeyEvent(keyCode), m_isRepeat(isRepeat) {}

    inline bool IsRepeat() const { return m_isRepeat; }

    // std::string ToString() const override
    //{
    //	return std::format("KeyPressedEvent: {} (repeat={})", m_KeyCode, m_IsRepeat);
    //}

    EVENT_CLASS_TYPE(KEY_PRESS);

private:
    bool m_isRepeat;
};

class KeyReleasedEvent : public KeyEvent {
public:
    KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}

    // log
    // std::string ToString() const override
    //{
    //	return std::format("KeyReleasedEvent: {}", m_KeyCode);
    // }

    EVENT_CLASS_TYPE(KEY_RELEASE);
};

// Mouse Events

class MouseMovedEvent : public Event {
public:
    MouseMovedEvent(double x, double y) : m_mouseX(x), m_mouseY(y) {}

    inline double GetX() const { return m_mouseX; }
    inline double GetY() const { return m_mouseY; }

    // std::string ToString() const override
    //{
    //	return std::format("MouseMovedEvent: {}, {}", m_MouseX, m_MouseY);
    // }

    EVENT_CLASS_TYPE(MOUSE_MOVE);

private:
    double m_mouseX, m_mouseY;
};

class MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(double xOffset, double yOffset) : m_xOffset(xOffset), m_yOffset(yOffset) {}

    inline double GetXOffset() const { return m_xOffset; }
    inline double GetYOffset() const { return m_yOffset; }

    // std::string ToString() const override
    //{
    //	return std::format("MouseScrolledEvent: {}, {}", m_XOffset, m_YOffset);
    // }

    EVENT_CLASS_TYPE(MOUSE_SCROLL);

private:
    double m_xOffset, m_yOffset;
};

class MouseButtonEvent : public Event {
public:
    inline int GetMouseButtonCode() const { return m_buttonCode; }

protected:
    MouseButtonEvent(int button) : m_buttonCode(button) {}

    int m_buttonCode;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
    MouseButtonPressedEvent(int buttonCode) : MouseButtonEvent(buttonCode) {}

    // std::string ToString() const override
    //{
    //	return std::format("MouseButtonPressedEvent: {}", m_Button);
    // }

    EVENT_CLASS_TYPE(MOUSE_PRESS);
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    MouseButtonReleasedEvent(int buttonCode) : MouseButtonEvent(buttonCode) {}

    // std::string ToString() const override
    //{
    //	return std::format("MouseButtonReleasedEvent: {}", m_Button);
    //}

    EVENT_CLASS_TYPE(MOUSE_RELEASE);
};

} // namespace zui
