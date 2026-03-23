#include "Engine.hpp"

#include "../Logger/Log.hpp"
#include "Application.hpp"

namespace zui {

void Engine::Init(Application* app) {
    m_app = app;
    m_window.UpdateConfig(m_app->SetWindowConfig());
    m_app->OnInit();
    Logger::Init();

    m_window.SetEventEmitCallback([this](Event& event) { m_app->OnEvent(event); });
}

void Engine::Run() {
    m_clock.Reset();
    while (m_app->m_running) {
        m_app->OnUpdate(m_clock.Tick());

        // update
        // clear
        // render
        m_window.Update();
    }
    m_app->OnShutdown();
}

} // namespace zui
