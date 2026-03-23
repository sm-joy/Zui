#pragma once
#include <cstdint>
#include <functional>

namespace zui {

enum class WindowMode : std::uint8_t { WINDOWED = 0, FULLSCREEN, BORDERLESS, COUNT };

class Event;

struct WinConfig {
    const char* Title = "Basic Window";
    int Width = 800;
    int Height = 600;
    bool Resizable = false;
    bool Vsync = false;
    WindowMode Mode = WindowMode::WINDOWED;

    std::function<void(Event&)> EventEmitCallback = [](Event&) {};

    constexpr int GetCenterX() const { return Width / 2; }
    constexpr int GetCenterY() const { return Height / 2; }
};

}
