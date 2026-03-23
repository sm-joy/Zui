#pragma once

#include <cstdint>
#include <functional>
#include <string>

namespace zui {

enum class EventType : std::uint8_t {
    NONE = 0,

    WINDOW_CLOSE,
    WINDOW_RESIZE,
    WINDOW_FOCUS,

    KEY_PRESS,
    KEY_RELEASE,

    MOUSE_PRESS,
    MOUSE_RELEASE,
    MOUSE_MOVE,
    MOUSE_SCROLL,

    // APP_START,
    // APP_STOP,
    // APP_UPDATE,
    // APP_RENDER,
    COUNT
};

class Event {
public:
    bool Handled = false;

    virtual ~Event() = default;
    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual std::string ToString() const { return GetName(); }
};

class EventDispatcher {
    template <typename T> using EventHandler = std::function<bool(T&)>;

public:
    EventDispatcher(Event& event) : m_event(event) {}

    template <typename T> bool On(EventHandler<T> handler) {
        if (m_event.Handled)
            return false;

        if (m_event.GetEventType() == T::GetStaticType()) {
            m_event.Handled = handler(static_cast<T&>(m_event));
            return true;
        }
        return false;
    }

private:
    Event& m_event;
};

} // namespace zui

#define EVENT_CLASS_TYPE(type)                                                                                         \
    static zui::EventType GetStaticType() {                                                                            \
        return zui::EventType::type;                                                                                   \
    }                                                                                                                  \
    virtual zui::EventType GetEventType() const override {                                                             \
        return GetStaticType();                                                                                        \
    }                                                                                                                  \
    virtual const char* GetName() const override {                                                                     \
        return #type;                                                                                                  \
    }
