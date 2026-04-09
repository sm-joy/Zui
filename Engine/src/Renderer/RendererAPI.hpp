#pragma once
#include <memory>
#include "../Values/Color.hpp"
#include "VertexArray.hpp"
#include "RendererConfig.hpp"

namespace zui {

class RendererAPI {
public:

    virtual ~RendererAPI() = default;

    virtual void Init() = 0;
    virtual void SetViewport(int x, int y, int width, int height) = 0;
    virtual void SetClearColor(const Color& color) = 0;
    virtual void Clear() = 0;
    virtual void DrawIndexed(const std::shared_ptr<VertexArray>& va, std::uint32_t indexCount = 0) = 0;

    static GraphicsAPI GetGraphicsAPI() { return s_api; }
    static std::unique_ptr<RendererAPI> Create();

private:
    static GraphicsAPI s_api;
};

} // namespace zui
