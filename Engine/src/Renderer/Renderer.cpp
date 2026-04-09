#include "Renderer.hpp"

#include "../Logger/Log.hpp"
#include "RenderCommand.hpp"
#include "RendererAPI.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"

namespace zui {

void Renderer::Init() {
    RenderCommand::Init();
    RenderCommand::SetClearColor(Color{0.1f, 0.1f, 0.1f, 1.0f});
}

void Renderer::Shutdown() {
    RenderCommand::Shutdown();
}

void Renderer::OnWindowResize(int w, int h) {
    RenderCommand::SetViewport(0, 0, w, h);
}

void Renderer::SetClearColor(const Color& color) {
    RenderCommand::SetClearColor(color);
}

void Renderer::Clear() {
    RenderCommand::Clear();
}

void Renderer::BeginScene() {}

void Renderer::EndScene() {}

void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& va) {
    if (!shader || !va) {
        LOGGER_ERROR("Renderer::Submit requires a valid shader and vertex array.");
        return;
    }

    shader->Bind();
    va->Bind();
    RenderCommand::DrawIndexed(va);
}

GraphicsAPI Renderer::GetAPI() {
    return RendererAPI::GetGraphicsAPI();
}

} // namespace zui
