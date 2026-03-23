#include <Zui.hpp>
class Game : public zui::Application {
    zui::WinConfig SetWindowConfig() override { return {.Title = "Game", .Width = 500, .Height = 500}; }
};

zui::Application* CreateApplication() {
    return new Game();
}
