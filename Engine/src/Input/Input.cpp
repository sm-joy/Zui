#include "Input.hpp"
#include "../Platform/GLFW/GLFWInput.hpp"
#include "../Logger/Log.hpp"
#include <memory>

namespace zui {

std::unique_ptr<Input> Input::s_instance = nullptr;

void Input::Init() {
    s_instance = std::make_unique<GLFWInput>();
    LOGGER_TRACE("[INPUT] Initialized.");
}

void Input::Shutdown() {
    s_instance.reset();
    LOGGER_TRACE("[INPUT] Shutdown.");
}

void Input::OnUpdate() {
    s_instance->ImplOnUpdate();
}

} // namespace zui