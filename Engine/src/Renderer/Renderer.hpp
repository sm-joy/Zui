#pragma once
#include "../Core/API.hpp"
#include "../Values/Color.hpp"
#include "RendererConfig.hpp"

#include <memory>

namespace zui {

class Shader;
class VertexArray;

class ZUI_API Renderer {
public:
    static void Init();
    static void Shutdown();
    static void OnWindowResize(int width, int height);

    static void SetClearColor(const Color& color);
    static void Clear();

    static void BeginScene();
    static void EndScene();
    static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& va);

    static GraphicsAPI GetAPI();
};

} // namespace zui
