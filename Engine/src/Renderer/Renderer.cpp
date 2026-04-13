#include "Renderer.hpp"

#include "../Logger/Log.hpp"
#include "Camera.hpp"
#include "RenderCommand.hpp"
#include "RendererAPI.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"

namespace zui {

std::unique_ptr<Renderer::SceneData> Renderer::s_sceneData = nullptr;

static std::uint32_t CalculateVertexCount(const std::shared_ptr<VertexArray>& va) {
    if (!va) {
        return 0;
    }

    const auto& vertexBuffers = va->GetVertexBuffers();
    if (vertexBuffers.empty() || !vertexBuffers.front()) {
        LOGGER_ERROR("Renderer::Submit requires at least one valid vertex buffer for non-indexed draws.");
        return 0;
    }

    const std::shared_ptr<VertexBuffer>& vertexBuffer = vertexBuffers.front();
    const std::uint32_t stride = vertexBuffer->GetBufferLayout().GetStride();
    if (stride == 0) {
        LOGGER_ERROR("Renderer::Submit could not infer vertex count because the vertex buffer layout stride is zero.");
        return 0;
    }

    const std::uint32_t size = vertexBuffer->GetSize();
    if (size % stride != 0) {
        LOGGER_WARN(
            "Vertex buffer size is not evenly divisible by its layout stride; truncating inferred vertex count.");
    }

    return size / stride;
}

void Renderer::Init() {
    s_sceneData = std::make_unique<SceneData>();
    RenderCommand::Init();
    RenderCommand::SetClearColor(Color{0.1f, 0.1f, 0.1f, 1.0f});
}

void Renderer::Shutdown() {
    s_sceneData.reset();
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

void Renderer::BeginScene(PerspectiveCamera& camera) {
    s_sceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene() {}

void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& va,
                      const glm::mat4& transform) {
    if (!va) {
        LOGGER_ERROR("Renderer::Submit requires a valid vertex array.");
        return;
    }
    if (!shader) {
        LOGGER_ERROR("Renderer::Submit requires a valid shader.");
        return;
    }

    const std::shared_ptr<IndexBuffer>& indexBuffer = va->GetIndexBuffer();

    shader->Bind();
    shader->SetMat4("u_ViewProjection", s_sceneData->ViewProjectionMatrix);
    shader->SetMat4("u_Model", transform);

    va->Bind();
    if (indexBuffer) {
        RenderCommand::DrawIndexed(va);
        return;
    }
    const std::uint32_t vertexCount = CalculateVertexCount(va);
    if (vertexCount == 0) {
        LOGGER_ERROR("Renderer::Submit could not determine a valid vertex count for non-indexed drawing.");
        return;
    }

    RenderCommand::DrawArrays(va, vertexCount);
}

void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& va,
                      std::uint32_t vertexCount, const glm::mat4& transform) {
    if (!shader || !va) {
        LOGGER_ERROR("Renderer::Submit requires a valid shader and vertex array.");
        return;
    }

    shader->Bind();
    shader->SetMat4("u_ViewProjection", s_sceneData->ViewProjectionMatrix);
    shader->SetMat4("u_Model", transform);
    va->Bind();

    if (va->GetIndexBuffer()) {
        RenderCommand::DrawIndexed(va);
        return;
    }

    if (vertexCount <= 0) {
        LOGGER_ERROR("Renderer::Submit requires a non-zero vertex count when drawing without an index buffer.");
        return;
    }

    RenderCommand::DrawArrays(va, vertexCount);
}

GraphicsAPI Renderer::GetAPI() {
    return RendererAPI::GetGraphicsAPI();
}

} // namespace zui
