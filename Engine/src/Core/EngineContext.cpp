#include "EngineContext.hpp"

#include "Engine.hpp"


namespace zui {

void EngineContext::HideCursor() const {
    Engine::GetInstance().GetWindow().HideCursor();
}

void EngineContext::ShowCursor() const {
    Engine::GetInstance().GetWindow().ShowCursor();
}

int EngineContext::GetWindowWidth() const {
    return Engine::GetInstance().GetWindow().GetWindowWidth();
}

int EngineContext::GetWindowHeight() const {
    return Engine::GetInstance().GetWindow().GetWindowHeight();
}

} // namespace zui