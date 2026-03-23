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

    template <typename TFunc, std::enable_if_t<std::is_invocable_r_v<void, TFunc, Event&>, int> = 0>
    void SetEventEmitCallback(TFunc&& callback) {
        m_winConfig.EventEmitCallback = std::forward<TFunc>(callback);
    }

private:
    WinConfig m_winConfig;
    GLFWwindow* m_windowHandle;

    void SetGlfwCallbacks();
};
} // namespace zui
