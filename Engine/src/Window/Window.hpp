#pragma once
#include "WindowConfig.hpp"
#include <memory>

struct GLFWwindow;

namespace zui {

class GraphicsContext;

class Window {
public:
    Window(const WinConfig& winConfig = WinConfig());
    ~Window();

    void UpdateConfig(const WinConfig& winCfg);
    void Update() const;
    GLFWwindow* GetWindowHandle() const;
    bool ShouldClose() const;

    template <typename TFunc> void SetEventEmitCallback(TFunc&& callback) {
        m_winConfig.EventEmitCallback = std::forward<TFunc>(callback);
    }

private:
    WinConfig m_winConfig;
    GLFWwindow* m_windowHandle = nullptr;
    bool m_glfwInitialized = false;
    std::unique_ptr<GraphicsContext> m_graphicsContext;

    bool CreateNativeWindow();
    void DestroyWindow();
    void SetGlfwCallbacks();
};
} // namespace zui
