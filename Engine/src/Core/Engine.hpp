#pragma once
#include "API.hpp"
#include "../Time/Time.hpp"
#include "../Window/Window.hpp"

namespace zui {

class Application;

class ZUI_API Engine {
public:
    static Engine& GetInstance() {
        static Engine sInstance;
        return sInstance;
    }

    void Init(Application* app);
    void Run();

private:
    Engine() = default;
    ~Engine() = default;
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(Engine&&) = delete;

    Clock m_clock;
    Window m_window;
    Application* m_app;
};

} // namespace zui
