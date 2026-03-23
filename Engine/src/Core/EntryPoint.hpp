#pragma once
#include "Engine.hpp"

extern zui::Application* CreateApplication();

int main() {
    zui::Application* app = CreateApplication();
    zui::Engine::GetInstance().Init(app);
    zui::Engine::GetInstance().Run();
    delete app;
    return 0;
}
