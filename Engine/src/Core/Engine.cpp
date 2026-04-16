#include "Engine.hpp"

#include "../Input/Input.hpp"
#include "../Logger/Log.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Time/Time.hpp"
#include "Application.hpp"

namespace zui {

void Engine::Init(Application* app) {
    Logger::Init();
    GProfiler::Init();

    SCOPED_PROFILE("Engine Init");
    m_app = app;

    GClock::Init();
    
    m_window.UpdateConfig(m_app->SetWindowConfig());
    if (!m_window.GetWindowHandle()) {
        LOGGER_CRITICAL("Engine Failed To Create a Window.");
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
    {
        SCOPED_PROFILE("Engine Run");
        if (!m_app) {
            LOGGER_CRITICAL("Application Is Invalid.");
            return;
        }
        if (!m_window.GetWindowHandle()) {
            LOGGER_CRITICAL("Application Window Is Invalid.");
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
    GProfiler::Shutdown();
}

const Window& Engine::GetWindow() const {
    return m_window;
}

} // namespace zui
