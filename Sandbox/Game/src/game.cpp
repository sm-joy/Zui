#include <Zui.hpp>

class MainMenuLayer : public zui::Layer {
    void OnAttach() override {
        LOGGER_TRACE("Heloo from Main Menu Layer");
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
