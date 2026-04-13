#pragma once
#include "../Core/API.hpp"

namespace zui {

class Event;
class FrameContext;

class ZUI_API Layer {
public:
    virtual ~Layer() = default;

    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnEvent(FrameContext& ctx, Event& event) {}
    virtual void OnUpdate(FrameContext& ctx, float dt) {}
    virtual void OnRender() {}
};

} // namespace zui
