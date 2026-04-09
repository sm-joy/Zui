#pragma once
#include "API.hpp"
#include "../Layer/LayerContext.hpp"
#include "../Window/WindowConfig.hpp"

#include <memory>

namespace zui {

class Event;
class LayerStack;

class ZUI_API Application {
public:
    Application();
    virtual ~Application();

    virtual void OnInit(LayerContext& layerContex) {}
    virtual void OnEvent(LayerContext& layerContex, Event& event) {}
    virtual void OnUpdate(LayerContext& layerContex, float dt) {}
    virtual void OnRender() {}
    virtual void OnShutdown() {}

    virtual WinConfig SetWindowConfig() { return WinConfig{}; }

private:
    friend class Engine;

    bool m_running = true;
    std::unique_ptr<LayerStack> m_layerStack;
    LayerContext m_layerContext;

    void MInit();
    void MUpdate(float dt);
    void MEvent(Event& event);
    void MRender();
    void MProcessLayerCommands();
};

} // namespace zui
