#pragma once
#include "API.hpp"
#include "../Layer/LayerContext.hpp"
#include "../Window/WindowConfig.hpp"

#include <memory>

namespace zui {

class Event;
class LayerStack;
class FrameContext;
class EngineContext;

class ZUI_API Application {
public:
    Application();
    virtual ~Application();

    virtual void OnInit(FrameContext& ctx) {}
    virtual void OnEvent(FrameContext& ctx, Event& event) {}
    virtual void OnUpdate(FrameContext& ctx, float dt) {}
    virtual void OnRender() {}
    virtual void OnShutdown() {}

    virtual WinConfig SetWindowConfig() { return WinConfig{}; }

private:
    friend class Engine;

    bool m_running = true;
    std::unique_ptr<LayerStack> m_layerStack;
    LayerContext m_layerContext;

    void MInit(EngineContext& ctx);
    void MUpdate(EngineContext& ctx, float dt);
    void MEvent(EngineContext& ctx, Event& event);
    void MRender();
    void MProcessLayerCommands();
};

} // namespace zui
