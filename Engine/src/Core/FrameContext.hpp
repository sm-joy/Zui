#pragma once
#include "../Layer/LayerContext.hpp"
#include "API.hpp"
#include "EngineContext.hpp"

namespace zui {

class ZUI_API FrameContext {
    public:
    EngineContext& Engine;
    LayerContext& Layer;

    FrameContext(EngineContext& engine, LayerContext& layer) : Engine(engine), Layer(layer) {}
};

} // namespace zui