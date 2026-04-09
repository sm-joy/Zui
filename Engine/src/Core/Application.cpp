#include "Application.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Event/Event.hpp"
#include "../Layer/LayerStack.hpp"

namespace zui {

Application::Application() : m_layerStack(std::make_unique<LayerStack>()) {}

Application::~Application() = default;

void Application::MEvent(Event& event) {
    Dispatch(event).On<WindowCloseEvent>([this](WindowCloseEvent& e) {
        m_running = false;
        return true;
    });
    Dispatch(event).On<WindowResizeEvent>([](WindowResizeEvent& e) {
        Renderer::OnWindowResize(static_cast<int>(e.GetWidth()), static_cast<int>(e.GetHeight()));
        return false;
    });

    OnEvent(m_layerContext, event);
    m_layerStack->PropagateEvent(m_layerContext, event);

}

void Application::MRender() {
    OnRender();
    m_layerStack->Renderlayers();
}

void Application::MInit() {
    OnInit(m_layerContext);
    MProcessLayerCommands();
}


void Application::MUpdate(float dt) {
    OnUpdate(m_layerContext, dt);
    m_layerStack->UpdateLayers(m_layerContext, dt);
    MProcessLayerCommands();
}

void Application::MProcessLayerCommands() {
    const LayerContext::LayerCommandList& layerCommands = m_layerContext.GetPendingCommands();

    for (const LayerCommand& command : layerCommands) {
        switch (command.Type) {
        case LayerCommandType::PUSH: {
            if (command.LayerConstructor) {
                m_layerStack->PushLayer(command.LayerConstructor());
            }
            break;
        }
        case LayerCommandType::POP: {
            m_layerStack->PopLayer();
            break;
        }
        case LayerCommandType::POP_ALL: {
            m_layerStack->PopAllLayers();
            break;
        }
        case LayerCommandType::INSERT: {
            break;
        }
        default:
            break;
        }
    }

    m_layerContext.Clear();
}

} // namespace zui
