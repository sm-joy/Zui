#include "Engine.hpp"
#include "Application.hpp"
#include "../Logger/Log.hpp"
#include "../Values/Color.hpp"

namespace zui {

void Engine::Init(Application* app) {
    m_app = app;
    m_window.UpdateConfig(m_app->SetWindowConfig());
    Logger::Init();
    m_app->MInit();

    m_window.SetEventEmitCallback([this](Event& event) { m_app->MEvent(event); });

    m_renderer.SetClearColor(colors::BLUE);
}

void Engine::Run() {
    m_clock.Reset();
    float dt = 0.0f;
    while (m_app->m_running) {
        dt = m_clock.Tick();
        m_app->MUpdate(dt);
        // render
        m_window.Update();
    }
    m_app->OnShutdown();
}

} // namespace zui
