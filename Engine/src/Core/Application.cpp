#include "Application.hpp"

#include "../Event/Event.hpp"
#include "../Layer/LayerStack.hpp"
#include "../Renderer/Renderer.hpp"
#include "FrameContext.hpp"
#include "../Time/Time.hpp"

namespace zui {

Application::Application() : m_layerStack(std::make_unique<LayerStack>()) {}

Application::~Application() = default;

void Application::MEvent(EngineContext& ctx, Event& event) {
    Dispatch(event).On<WindowCloseEvent>([this](WindowCloseEvent& e) {
        m_running = false;
        return true;
    });
    Dispatch(event).On<WindowResizeEvent>([](WindowResizeEvent& e) {
        Renderer::OnWindowResize(static_cast<int>(e.GetWidth()), static_cast<int>(e.GetHeight()));
        return false;
    });

    FrameContext context{ctx, m_layerContext};
    OnEvent(context, event);
    m_layerStack->PropagateEvent(context, event);
}

void Application::MRender() {
    OnRender();
    m_layerStack->Renderlayers();
}

void Application::MInit(EngineContext& ctx) {
    SCOPED_PROFILE("Aplication Internal Init");
    FrameContext context{ctx, m_layerContext};
    OnInit(context);
    MProcessLayerCommands();
}

void Application::MUpdate(EngineContext& ctx, float dt) {
    FrameContext context{ctx, m_layerContext};
    OnUpdate(context, dt);
    m_layerStack->UpdateLayers(context, dt);
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
