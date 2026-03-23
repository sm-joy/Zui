#pragma once

#include <cstdint>
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

    APP_START,
    APP_STOP,
    APP_UPDATE,
    APP_RENDER,

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
public:
    EventDispatcher(Event& event) : m_event(event) {}

    template <typename TEvent, typename TFunc> EventDispatcher& On(TFunc&& handler) {
        if (!m_event.Handled && m_event.GetEventType() == TEvent::GetStaticType()) {
            m_event.Handled = std::forward<TFunc>(handler)(static_cast<TEvent&>(m_event));
        }

        return *this;
    }

private:
    Event& m_event;
};

inline EventDispatcher Dispatch(Event& event) {
    return EventDispatcher(event);
}


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
