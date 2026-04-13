#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <Zui.hpp>

class MainMenuLayer : public zui::Layer {
public:
    zui::PerspectiveCameraController CameraController{ 500.0f/500.0f };
    std::shared_ptr<zui::Shader> ShaderProgram;
    std::shared_ptr<zui::VertexBuffer> VertexBfr;
    std::shared_ptr<zui::VertexArray> VertexArr;

    float Vertices[108] = {
        -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f,
        0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,

        -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,

        0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f,
        0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,
        0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f,

        -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f,
    };

    glm::vec3 CubePositions[10] = {glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
                                   glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
                                   glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
                                   glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
                                   glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

    void OnAttach() override {
        LOGGER_TRACE("Hello from Main Menu Layer");
        zui::Renderer::SetClearColor(zui::colors::DARK_GRAY);

        VertexArr = zui::VertexArray::Create();
        VertexBfr = zui::VertexBuffer::Create(Vertices, sizeof(Vertices));
        VertexBfr->SetLayout({{zui::ShaderDataType::FLOAT3, "aPos"}});

        ShaderProgram = zui::Shader::CreateFromFile("Cube", "Sandbox/assets/basic_shader.glsl");

        VertexArr->AddVertexBuffer(VertexBfr);
    }

    void OnUpdate(zui::FrameContext& ctx, float dt) override {
        CameraController.OnUpdate(dt);
    }

    void OnEvent(zui::FrameContext& ctx, zui::Event& event) override {
        CameraController.OnEvent(event);
    }

    void OnRender() override {
        zui::Renderer::BeginScene(CameraController.GetCamera());
        for (unsigned int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, CubePositions[i]);
            float angle = 20.0f * static_cast<float>(i);
            model = glm::rotate(model, (float)(zui::GClock::GetElapsedTime()), glm::vec3(0.5f, 1.0f, 0.0f));

            zui::Renderer::Submit(ShaderProgram, VertexArr, model);
        }
        zui::Renderer::EndScene();
    }
};

class Game : public zui::Application {
    void OnInit(zui::FrameContext& ctx) override {
        LOGGER_TRACE("Hello from application");
        ctx.Layer.PushLayer<MainMenuLayer>();
    }
    zui::WinConfig SetWindowConfig() override {
        return {.Title = "Game", .Width = 500, .Height = 500, .Resizable = true};
    }
};

zui::Application* CreateApplication() {
    return new Game();
}
