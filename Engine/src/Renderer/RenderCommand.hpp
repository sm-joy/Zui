#pragma once
#include "../Values/Color.hpp"
#include "RendererAPI.hpp"
#include "VertexArray.hpp"

#include <memory>

namespace zui {

class RenderCommand {
public:
    static void Init();
    static void Shutdown();
    static void SetViewport(int x, int y, int w, int h);
    static void SetClearColor(const Color& c);
    static void Clear();
    static void DrawIndexed(const std::shared_ptr<VertexArray>& va, std::uint32_t indexCount = 0,
                            std::uint32_t baseIndex = 0, std::uint32_t baseVertex = 0);
    static void DrawArrays(const std::shared_ptr<VertexArray>& va, std::uint32_t vertexCount,
                           std::uint32_t baseVertex = 0);

private:
    static std::unique_ptr<RendererAPI> s_rendererAPI;
};

} // namespace zui
