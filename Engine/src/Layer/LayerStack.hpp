#pragma once
#include "Layer.hpp"

#include <memory>
#include <vector>

namespace zui {

class LayerContext;
class Event;

class LayerStack {
public:
	LayerStack() = default;
	~LayerStack();

    LayerStack(const LayerStack&) = delete;
    LayerStack& operator=(const LayerStack&) = delete;
    LayerStack(LayerStack&&) noexcept = default;
    LayerStack& operator=(LayerStack&&) noexcept = default;

	void PushLayer(std::unique_ptr<Layer> layer);
	void PopLayer();
	void PopAllLayers();

	void UpdateLayers(LayerContext& layerContext, float dt);
	void Renderlayers();
	void PropagateEvent(LayerContext& layerContext, Event& event);


	bool IsEmpty() const;
	size_t LayerCount() const;

	auto begin() { return m_layers.begin(); }
	auto end() { return m_layers.end(); }
	auto begin() const { return m_layers.begin(); }
	auto end() const { return m_layers.end(); }

private:
	std::vector<std::unique_ptr<Layer>> m_layers;
};

}
