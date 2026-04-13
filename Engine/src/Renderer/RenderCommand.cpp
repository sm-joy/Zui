#include "RenderCommand.hpp"
#include "RendererAPI.hpp"

namespace zui {

std::unique_ptr<RendererAPI> RenderCommand::s_rendererAPI = nullptr;

void RenderCommand::Init() {
    if (!s_rendererAPI) {
        s_rendererAPI = RendererAPI::Create();
    }
    s_rendererAPI->Init();
}

void RenderCommand::Shutdown() {
    s_rendererAPI.reset();
}

void RenderCommand::SetViewport(int x, int y, int w, int h) {
    if (!s_rendererAPI) return;
    s_rendererAPI->SetViewport(x, y, w, h);
}

void RenderCommand::SetClearColor(const Color& c) {
    if (!s_rendererAPI) return;
    s_rendererAPI->SetClearColor(c);
}

void RenderCommand::Clear() {
    if (!s_rendererAPI) return;
    s_rendererAPI->Clear();
}

void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& va, std::uint32_t indexCount) {
    if (!s_rendererAPI) return;
    s_rendererAPI->DrawIndexed(va, indexCount);
}

void RenderCommand::DrawArrays(const std::shared_ptr<VertexArray>& va, std::uint32_t vertexCount) {
    if (!s_rendererAPI) return;
    s_rendererAPI->DrawArrays(va, vertexCount);
}

} // namespace zui
