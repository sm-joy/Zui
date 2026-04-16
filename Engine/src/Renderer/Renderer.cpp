#include "Renderer.hpp"

#include "../Logger/Log.hpp"
#include "../Time/Time.hpp"
#include "Camera.hpp"
#include "Material.hpp"
#include "Mesh.hpp"
#include "RenderCommand.hpp"
#include "RendererAPI.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"

#include <memory>

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
    SCOPED_PROFILE("Renderer Init");
    s_sceneData = std::make_unique<SceneData>();
    RenderCommand::Init();
    RenderCommand::SetClearColor(Color{0.1f, 0.1f, 0.1f, 1.0f});
}

void Renderer::Shutdown() {
    SCOPED_PROFILE("Renderer Shutdown");
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

void Renderer::Submit(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material, const glm::mat4& transform) {
    if (!mesh) {
        LOGGER_ERROR("Renderer::Submit requires a valid mesh.");
        return;
    }
    if (!material) {
        LOGGER_ERROR("Renderer::Submit requires a valid material.");
        return;
    }
    if (!mesh->GetVertexArray()) {
        LOGGER_ERROR("Renderer::Submit requires a valid vertex array.");
        return;
    }
    if (!material->GetShader()) {
        LOGGER_ERROR("Renderer::Submit requires a valid material.");
        return;
    }

    material->Bind();
    const std::shared_ptr<Shader> shader = material->GetShader();
    shader->SetMat4("u_ViewProjection", s_sceneData->ViewProjectionMatrix);
    shader->SetMat4("u_Model", transform);

    mesh->Bind();
    if (mesh->IsIndexed()) {
        RenderCommand::DrawIndexed(mesh->GetVertexArray());
    }
    else {
        RenderCommand::DrawArrays(mesh->GetVertexArray(), mesh->GetVertexCount());
    }

}

GraphicsAPI Renderer::GetAPI() {
    return RendererAPI::GetGraphicsAPI();
}

} // namespace zui
