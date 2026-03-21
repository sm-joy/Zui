#pragma once

namespace zui {

class Application {
public:
    Application();
    virtual ~Application() = default;

    virtual void OnInit() {}
    virtual void OnEvent();
    virtual void OnUpdate(float dt);
    virtual void OnShutdown() {}

private:
    friend class Engine;

    bool m_running = true;
};

} // namespace zui
