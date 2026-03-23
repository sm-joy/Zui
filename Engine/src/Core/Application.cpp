#include "Application.hpp"

#include "../Event/Event.hpp"

namespace zui {

Application::Application() {}

void Application::OnEvent(Event& event) {
    Dispatch(event).On<WindowCloseEvent>([this](WindowCloseEvent& e) {
        m_running = false;
        return true;
    });
}

void Application::OnUpdate(float dt) {}

} // namespace zui
