#pragma once
#include "../Window/Window.hpp"
#include "API.hpp"
#include "EngineContext.hpp"

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
    const Window& GetWindow() const;

private:
    Engine() = default;
    ~Engine() = default;
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(Engine&&) = delete;

    EngineContext m_engineContext;
    Window m_window;
    Application* m_app;
};

} // namespace zui
