#include <Zui.hpp>
class Game: public zui::Application {
    void OnInit() override {
        LOGGER_INFO("Hello from Game!");
    }
};

zui::Application* CreateApplication() {
    return new Game();
}
