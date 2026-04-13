#pragma once
#include "../Core/API.hpp"

#include <cstdint>
#include <functional>
#include <memory>
#include <vector>

namespace zui {

class Layer;

enum class LayerCommandType : std::uint8_t { PUSH, POP, POP_ALL, INSERT };

struct LayerCommand {
    using LayerConstructorFunc = std::function<std::unique_ptr<Layer>()>;

    LayerCommandType Type;
    LayerConstructorFunc LayerConstructor;
    int InsertIndex = -1;

    LayerCommand(LayerCommandType type) : Type(type), LayerConstructor(nullptr) {}

    LayerCommand(LayerCommandType type, LayerConstructorFunc layerConstructor)
        : Type(type), LayerConstructor(std::move(layerConstructor)) {}

    LayerCommand(LayerCommandType type, LayerConstructorFunc layerConstructor, int insertIndex)
        : Type(type), LayerConstructor(std::move(layerConstructor)), InsertIndex(insertIndex) {}
};

class ZUI_API LayerContext {
public:
    using LayerCommandList = std::vector<LayerCommand>;

    LayerContext() = default;
    ~LayerContext() { Clear(); }

    LayerContext(const LayerContext&) = default;
    LayerContext& operator=(const LayerContext&) = default;
    LayerContext(LayerContext&&) noexcept = default;
    LayerContext& operator=(LayerContext&&) noexcept = default;

    template <typename TLayer, typename... Args> void PushLayer(Args&&... args) {
        std::tuple<Args&&...> tArgs = std::make_tuple(std::forward<Args>(args)...);
        m_pendingCommands.emplace_back(LayerCommandType::PUSH, [tArgs]() mutable {
            return std::apply(
                [](auto&&... aArgs) { return std::make_unique<TLayer>(std::forward<decltype(aArgs)>(aArgs)...); },
                std::move(tArgs));
        });
    }

    void PopLayer() { m_pendingCommands.emplace_back(LayerCommandType::POP); }
    void PopAllLayers() { m_pendingCommands.emplace_back(LayerCommandType::POP_ALL); }

    template <typename TLayer, typename... Args> void TransitionTo(Args&&... args) {
        PopLayer();
        PushLayer<TLayer>(std::forward<Args>(args)...);
    }

    template <typename TLayer, typename... Args> void ReplaceAll(Args&&... args) {
        PopAllLayers();
        PushLayer<TLayer>(std::forward<Args>(args)...);
    }

    void Clear() { m_pendingCommands.clear(); }

    const LayerCommandList& GetPendingCommands() const { return m_pendingCommands; }

private:
    LayerCommandList m_pendingCommands;
};

} // namespace zui
