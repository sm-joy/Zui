#pragma once
#include "../Time/Time.hpp"
#include "Application.hpp"

namespace zui {

class Application;

class Engine {
public:
    static Engine& GetInstance() {
        static Engine sInstance;
        return sInstance;
    }

    void Init();
    void Run(Application* app);

private:
    Engine() = default;
    ~Engine() = default;
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(Engine&&) = delete;

    Clock m_clock;
};

} // namespace zui
