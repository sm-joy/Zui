#include <cstdint>
#include <Zui.hpp>
#include <memory>

class MainMenuLayer : public zui::Layer {
public:

    std::shared_ptr<zui::Shader> ShaderProgram;
    std::shared_ptr<zui::VertexBuffer> VertexBfr;
    std::shared_ptr<zui::IndexBuffer> IndexBfr;
    std::shared_ptr<zui::VertexArray> VertexArr;

    const char* VertexSrc = R"(
#version 330 core
layout(location = 0) in vec3 a_Position;

void main() {
    gl_Position = vec4(a_Position, 1.0);
}
)";

const char* FragmentSrc = R"(
#version 330 core
out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 0.5, 0.2, 1.0); // orange-ish
}
)";

    void OnAttach() override {
        LOGGER_TRACE("Heloo from Main Menu Layer");
        zui::Renderer::SetClearColor(zui::colors::DARK_GRAY);

        float vertices[12] = {
            // positions (x, y, z)
            -0.5f, -0.5f, 0.0f, // bottom-left
            0.5f,  -0.5f, 0.0f, // bottom-right
            0.5f,  0.5f,  0.0f, // top-right
            -0.5f, 0.5f,  0.0f  // top-left
        };

        std::uint32_t indices[6] = {
            0, 1, 2, // first triangle
            2, 3, 0  // second triangle
        };

        VertexArr = zui::VertexArray::Create();
        VertexBfr = zui::VertexBuffer::Create(vertices, sizeof(vertices));
        VertexBfr->SetLayout({
            {zui::ShaderDataType::FLOAT3, "a_Position"}
        });
        IndexBfr = zui::IndexBuffer::Create(indices, 6);
        std::shared_ptr<zui::ShaderStage> vertexStage =
            zui::ShaderStage::CreateFromSource(zui::ShaderStageType::VERTEX, VertexSrc);
        std::shared_ptr<zui::ShaderStage> fragmentStage =
            zui::ShaderStage::CreateFromSource(zui::ShaderStageType::FRAGMENT, FragmentSrc);
        ShaderProgram = zui::Shader::Create("Quad",
                                            std::vector<std::shared_ptr<zui::ShaderStage>>{vertexStage, fragmentStage});

        VertexArr->AddVertexBuffer(VertexBfr);
        VertexArr->SetIndexBuffer(IndexBfr);

    }

    void OnRender() override {
        zui::Renderer::Submit(ShaderProgram, VertexArr);
    }
};

class Game : public zui::Application {
    void OnInit(zui::LayerContext& layerContext) override {
        LOGGER_TRACE("Hello from application");
        layerContext.PushLayer<MainMenuLayer>();
    }
    zui::WinConfig SetWindowConfig() override { return {.Title = "Game", .Width = 500, .Height = 500}; }
};

zui::Application* CreateApplication() {
    return new Game();
}
