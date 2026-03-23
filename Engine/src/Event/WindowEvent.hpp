#pragma once

#include "Event.hpp"

namespace zui {

class WindowCloseEvent : public Event {
public:
    WindowCloseEvent() {};
    EVENT_CLASS_TYPE(WINDOW_CLOSE);
};

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(std::uint32_t width, std::uint32_t height) : m_width(width), m_height(height) {}

    inline std::uint32_t GetWidth() const { return m_width; }
    inline std::uint32_t GetHeight() const { return m_height; }

//     std::string ToString() const override { return {"WindowResizeEvent: {}, {}", m_width, m_height}; }

    EVENT_CLASS_TYPE(WINDOW_RESIZE);

private:
    std::uint32_t m_width, m_height;
};
} // namespace zui
