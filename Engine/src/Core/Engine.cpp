#include "Engine.hpp"
#include "Application.hpp"
#include "../Logger/Log.hpp"
#include "../Values/Color.hpp"

namespace zui {

void Engine::Init(Application* app) {
    m_app = app;
    Logger::Init();
    m_window.SetEventEmitCallback([this](Event& event) { m_app->MEvent(event); });
    m_window.UpdateConfig(m_app->SetWindowConfig());
    if (!m_window.GetWindowHandle()) {
        LOGGER_CRITICAL("Engine failed to create a window.");
        m_app->m_running = false;
        return;
    }

    Renderer::Init();
    m_app->MInit();
}

void Engine::Run() {
    if (!m_app || !m_window.GetWindowHandle()) {
        return;
    }

    m_clock.Reset();
    float dt = 0.0f;
    while (m_app->m_running && !m_window.ShouldClose()) {
        dt = m_clock.Tick();
        m_app->MUpdate(dt);
        Renderer::BeginScene();
        Renderer::Clear();
        m_app->MRender();
        Renderer::EndScene();
        m_window.Update();
    }
    m_app->OnShutdown();
    Renderer::Shutdown();
}

} // namespace zui
