#pragma once
#include <cstdint>

namespace zui {

enum class WindowMode : std::uint8_t { WINDOWED = 0, FULLSCREEN, BORDERLESS, COUNT };

struct WinConfig {
    const char* Title = "Basic Window";
    int Width = 800;
    int Height = 600;
    bool Resizable = false;
    bool Vsync = false;
    WindowMode Mode = WindowMode::WINDOWED;

    constexpr int GetCenterX() const { return Width / 2; }
    constexpr int GetCenterY() const { return Height / 2; }
};

}
