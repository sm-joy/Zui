#include "LayerStack.hpp"

#include "Layer.hpp"
#include "LayerContext.hpp"

namespace zui {

LayerStack::~LayerStack() {
    PopAllLayers();
}

bool LayerStack::IsEmpty() const {
    return m_layers.empty();
}

size_t LayerStack::LayerCount() const {
    return m_layers.size();
}

void LayerStack::PushLayer(std::unique_ptr<Layer> layer) {
    layer->OnAttach();
    m_layers.push_back(std::move(layer));
}

void LayerStack::PopLayer() {
    if (IsEmpty())
        return;

    m_layers.back()->OnDetach();
    m_layers.pop_back();
}
void LayerStack::PopAllLayers() {
    for (auto& layer : m_layers) {
        layer->OnDetach();
    }
    m_layers.clear();
}

void LayerStack::UpdateLayers(LayerContext& layerContext, float dt) {
    for (auto& layer : m_layers) {
        layer->OnUpdate(layerContext, dt);
    }
}
void LayerStack::PropagateEvent(LayerContext& layerContext, Event& event) {
    for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it) {
        (*it)->OnEvent(layerContext, event);
    }
}

} // namespace zui
