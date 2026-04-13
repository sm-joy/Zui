#pragma once
#include "../Core/API.hpp"
#include "../Values/Color.hpp"
#include "RendererConfig.hpp"

#include <glm/glm.hpp>
#include <memory>

namespace zui {

class Shader;
class VertexArray;
class PerspectiveCamera;

class ZUI_API Renderer {
public:
    static void Init();
    static void Shutdown();
    static void OnWindowResize(int width, int height);

    static void SetClearColor(const Color& color);
    static void Clear();

    static void BeginScene(PerspectiveCamera& camera);
    static void EndScene();
    static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& va,
                       const glm::mat4& transform = glm::mat4(1.0f));
    static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& va,
                       std::uint32_t vertexCount, const glm::mat4& transform = glm::mat4(1.0f));

    static GraphicsAPI GetAPI();

private:
    struct SceneData {
        glm::mat4 ViewProjectionMatrix;
    };
    static std::unique_ptr<SceneData> s_sceneData;
};

} // namespace zui
