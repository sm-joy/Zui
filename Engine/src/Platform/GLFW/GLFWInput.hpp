#pragma once
#include "../../Input/Input.hpp"

#include <array>
#include <GLFW/glfw3.h>


namespace zui {

class GLFWInput : public Input {
public:
    GLFWInput() = default;
    ~GLFWInput() override = default;

private:
    static constexpr int KEY_COUNT = GLFW_KEY_LAST + 1;
    static constexpr int BUTTON_COUNT = GLFW_MOUSE_BUTTON_LAST + 1;

    std::array<bool, KEY_COUNT> m_curKeys = {};
    std::array<bool, KEY_COUNT> m_prevKeys = {};
    std::array<bool, BUTTON_COUNT> m_curBtns = {};
    std::array<bool, BUTTON_COUNT> m_prevBtns = {};


    void ImplOnUpdate() override;

    bool ImplIsKeyPressed(KeyCode key) const override;
    bool ImplIsKeyDown(KeyCode key) const override;
    bool ImplIsKeyReleased(KeyCode key) const override;
    bool ImplIsMouseButtonPressed(MouseCode btn) const override;
    bool ImplIsMouseButtonDown(MouseCode btn) const override;
    bool ImplIsMouseButtonReleased(MouseCode btn) const override;
    glm::dvec2 ImplGetMousePosition() const override;

};

} // namespace zui