#pragma once
#include "Engine.hpp"

extern zui::Application* CreateApplication();

int main() {
    zui::Application* app = CreateApplication();
    zui::Engine::GetInstance().Init();
    zui::Engine::GetInstance().Run(app);
    delete app;
    return 0;
}
