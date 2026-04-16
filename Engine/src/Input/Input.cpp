#include "Input.hpp"
#include "../Platform/GLFW/GLFWInput.hpp"
#include "../Time/Time.hpp"
#include <memory>

namespace zui {

std::unique_ptr<Input> Input::s_instance = nullptr;

void Input::Init() {
    SCOPED_PROFILE("Input Init");
    s_instance = std::make_unique<GLFWInput>();
}

void Input::Shutdown() {
    SCOPED_PROFILE("Input Shutdown");
    s_instance.reset();
}

void Input::OnUpdate() {
    s_instance->ImplOnUpdate();
}

} // namespace zui