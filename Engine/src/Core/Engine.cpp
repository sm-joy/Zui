#include "Engine.hpp"

#include "../Input/Input.hpp"
#include "../Logger/Log.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Time/Time.hpp"
#include "Application.hpp"

namespace zui {

void Engine::Init(Application* app) {
    m_app = app;

    GClock::Init();
    Logger::Init();
    
    m_window.UpdateConfig(m_app->SetWindowConfig());
    if (!m_window.GetWindowHandle()) {
        LOGGER_CRITICAL("Engine failed to create a window.");
        m_app->m_running = false;
        return;
    }
    
    m_window.SetEventEmitCallback([this](Event& event) {  // this have to be put after Window.UpdateConfig
        m_app->MEvent(m_engineContext, event);
    });

    Renderer::Init();

    Input::Init();
    m_app->MInit(m_engineContext);

}

void Engine::Run() {
    if (!m_app || !m_window.GetWindowHandle()) {
        return;
    }

    GClock::Reset();
    float dt = 0.0f;
    while (m_app->m_running && !m_window.ShouldClose()) {
        dt = GClock::Tick();
        Input::OnUpdate();
        m_app->MUpdate(m_engineContext, dt);

        Renderer::Clear();
        m_app->MRender();

        m_window.Update();
    }
    m_app->OnShutdown();
    Renderer::Shutdown();
    Input::Shutdown();
}

const Window& Engine::GetWindow() const {
    return m_window;
}

} // namespace zui
