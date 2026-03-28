#pragma once

namespace zui {

class LayerContext;
class Event;

class Layer {
public:
    virtual ~Layer() = default;

    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnEvent(LayerContext& context, Event& event) {}
    virtual void OnUpdate(LayerContext& context, float dt) {}
    virtual void OnRender() {}
};

} // namespace zui
