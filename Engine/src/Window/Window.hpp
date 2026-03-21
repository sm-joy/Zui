#pragma once
#include "WindowConfig.hpp"

struct GLFWwindow;

namespace zui {

class Window {
public:
    Window(const WinConfig& winConfig = WinConfig());
    ~Window();

    void UpdateConfig(const WinConfig& winCfg);
    void Update() const;
    GLFWwindow* GetWindowHandle() const;
    bool ShouldClose() const;

private:
    WinConfig m_winConfig;
    GLFWwindow* m_window;
};
} // namespace zui
