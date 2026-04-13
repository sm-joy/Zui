#pragma once

#include "Event.hpp"
#include "../Input/KeyCode.hpp"
#include "../Input/MouseCode.hpp"

namespace zui {

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
    inline MouseCode GetMouseButtonCode() const { return m_buttonCode; }

protected:
    MouseButtonEvent(int button) : m_buttonCode(static_cast<MouseCode>(button)) {}

    MouseCode m_buttonCode;
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
