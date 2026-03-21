#include "Engine.hpp"
#include "Application.hpp"
#include "../Logger/Log.hpp"

namespace zui {

void Engine::Init() {
    Logger::Init();
}

void Engine::Run(Application* app) {
    app->OnInit();
    m_clock.Reset();
    while (app->m_running) {
        app->OnUpdate(m_clock.Tick());

        // update
        // clear
        // render
        // window update
    }
    app->OnShutdown();
}

} // namespace zui
