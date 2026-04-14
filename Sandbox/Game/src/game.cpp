#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <Zui.hpp>

class MainMenuLayer : public zui::Layer {
public:
    zui::PerspectiveCameraController CameraController{500.0f / 500.0f};
    std::shared_ptr<zui::Shader> ShaderProgram;
    std::shared_ptr<zui::VertexBuffer> VertexBfr;
    std::shared_ptr<zui::VertexArray> VertexArr;
    std::shared_ptr<zui::Texture2D> Texture;

    float Vertices[180] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

        -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

    glm::vec3 CubePositions[50] = {
        {0.0f, 0.0f, 0.0f},    {2.0f, 5.0f, -15.0f},   {-1.5f, -2.2f, -2.5f},  {-3.8f, -2.0f, -12.3f},
        {2.4f, -0.4f, -3.5f},  {-1.7f, 3.0f, -7.5f},   {1.3f, -2.0f, -2.5f},   {1.5f, 2.0f, -2.5f},
        {1.5f, 0.2f, -1.5f},   {-1.3f, 1.0f, -1.5f},   {-5.0f, -1.0f, -5.0f},  {-3.0f, -1.0f, -5.0f},
        {-1.0f, -1.0f, -5.0f}, {1.0f, -1.0f, -5.0f},   {3.0f, -1.0f, -5.0f},   {5.0f, -1.0f, -5.0f},
        {-5.0f, 1.0f, -10.0f}, {-2.5f, 1.5f, -10.0f},  {0.0f, 2.0f, -10.0f},   {2.5f, 1.5f, -10.0f},
        {5.0f, 1.0f, -10.0f},  {-6.0f, -2.0f, -15.0f}, {-3.0f, 2.0f, -15.0f},  {0.0f, -3.0f, -15.0f},
        {3.0f, 3.0f, -15.0f},  {6.0f, -1.0f, -15.0f},  {4.2f, 2.8f, -6.0f},    {-4.5f, 3.2f, -8.0f},
        {3.7f, -2.5f, -9.0f},  {-2.2f, 4.0f, -11.0f},  {0.5f, -4.0f, -13.0f},  {0.0f, 5.0f, -8.0f},
        {0.0f, 3.0f, -8.0f},   {0.0f, 1.0f, -8.0f},    {0.0f, -1.0f, -8.0f},   {0.0f, -3.0f, -8.0f},
        {-7.0f, 0.0f, -12.0f}, {-7.0f, 2.0f, -14.0f},  {-7.0f, -2.0f, -16.0f}, {7.0f, 0.0f, -12.0f},
        {7.0f, 2.0f, -14.0f},  {7.0f, -2.0f, -16.0f},  {-8.0f, 1.0f, -20.0f},  {-5.0f, -3.0f, -22.0f},
        {0.0f, 0.0f, -25.0f},  {5.0f, 3.0f, -22.0f},   {8.0f, -1.0f, -20.0f}};

    void OnAttach() override {

        zui::Renderer::SetClearColor(zui::colors::DARK_GRAY);

        Texture = zui::Texture2D::Create("Sandbox/assets/dd.jpeg");

        VertexArr = zui::VertexArray::Create();
        VertexBfr = zui::VertexBuffer::Create(Vertices, sizeof(Vertices));
        VertexBfr->SetLayout({{zui::ShaderDataType::FLOAT3, "aPos"}, {zui::ShaderDataType::FLOAT2, "aTexCoord"}});

        ShaderProgram = zui::Shader::CreateFromFile("Cube", "Sandbox/assets/basic_shader.glsl");

        VertexArr->AddVertexBuffer(VertexBfr);
    }

    void OnUpdate(zui::FrameContext& ctx, float dt) override { CameraController.OnUpdate(dt); }

    void OnEvent(zui::FrameContext& ctx, zui::Event& event) override { CameraController.OnEvent(event); }

    void OnRender() override {
        zui::Renderer::BeginScene(CameraController.GetCamera());
        for (unsigned int i = 0; i < 47; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, CubePositions[i]);
            float angle = 20.0f * static_cast<float>(i);
            model = glm::rotate(model, (float)(zui::GClock::GetElapsedTime()), glm::vec3(0.5f, 1.0f, 0.0f));

            Texture->Bind(0);
            ShaderProgram->Bind();
            ShaderProgram->Set("u_Texture", 0);
            zui::Renderer::Submit(ShaderProgram, VertexArr, model);
        }
        zui::Renderer::EndScene();
    }
};

class Game : public zui::Application {
    void OnInit(zui::FrameContext& ctx) override {
        ctx.Layer.PushLayer<MainMenuLayer>();
    }
    zui::WinConfig SetWindowConfig() override {
        return {.Title = "Game", .Width = 500, .Height = 500, .Resizable = true};
    }
};

zui::Application* CreateApplication() {
    return new Game();
}
