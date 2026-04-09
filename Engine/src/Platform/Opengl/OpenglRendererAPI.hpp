#pragma once
#include "../../Renderer/RendererAPI.hpp"
#include <memory>

namespace zui {

class OpenglRendererAPI : public RendererAPI {
public:
    void Init() override;
    void SetViewport(int x, int y, int w, int h) override;
    void SetClearColor(const Color& color) override;
    void Clear() override;
    void DrawIndexed(const std::shared_ptr<VertexArray>& va, std::uint32_t indexCount = 0) override;
};

} // namespace zui
