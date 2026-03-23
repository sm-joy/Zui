#pragma once
#include "API.hpp"
#include "../Window/WindowConfig.hpp"

namespace zui {

class Event;

class ZUI_API Application {
public:
    Application();
    virtual ~Application() = default;

    virtual void OnInit() {}
    virtual void OnEvent(Event& event);

    virtual void OnUpdate(float dt);
    virtual void OnShutdown() {}

    virtual WinConfig SetWindowConfig() { return WinConfig{}; }

private:
    friend class Engine;

    bool m_running = true;
};

} // namespace zui
