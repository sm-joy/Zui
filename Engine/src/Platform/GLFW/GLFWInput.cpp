#include "GLFWInput.hpp"

#include "../../Core/Engine.hpp"

namespace zui {

#define TOGLFWKEY(k) static_cast<int>(key)

#define TOGLFWBUTTON(btn) static_cast<int>(btn)

void GLFWInput::ImplOnUpdate() {
    GLFWwindow* win = static_cast<GLFWwindow*>(Engine::GetInstance().GetWindow().GetNativeHandler());

    m_prevKeys = m_curKeys;
    m_prevBtns = m_curBtns;

    for (int i = 0; i < KEY_COUNT; ++i) {
        m_curKeys[i] = (glfwGetKey(win, i) == GLFW_PRESS);
    }

    for (int i = 0; i < BUTTON_COUNT; ++i) {
        m_curBtns[i] = (glfwGetMouseButton(win, i) == GLFW_PRESS);
    }
}

bool GLFWInput::ImplIsKeyPressed(KeyCode key) const {
    int k = TOGLFWKEY(key);
    return k >= 0 && k < KEY_COUNT && m_curKeys[k];
}

bool GLFWInput::ImplIsKeyDown(KeyCode key) const {
    int k = TOGLFWKEY(key);
    return k >= 0 && k < KEY_COUNT && m_curKeys[k] && !m_prevKeys[k];
}

bool GLFWInput::ImplIsKeyReleased(KeyCode key) const {
    int k = TOGLFWKEY(key);
    return k >= 0 && k < KEY_COUNT && !m_curKeys[k] && m_prevKeys[k];
}

bool GLFWInput::ImplIsMouseButtonPressed(MouseCode btn) const {
    int b = TOGLFWBUTTON(btn);
    return b >= 0 && b < BUTTON_COUNT && m_curBtns[b];
}

bool GLFWInput::ImplIsMouseButtonDown(MouseCode btn) const {
    int b = TOGLFWBUTTON(btn);
    return b >= 0 && b < BUTTON_COUNT && m_curBtns[b] && !m_prevBtns[b];
}

bool GLFWInput::ImplIsMouseButtonReleased(MouseCode btn) const {
    int b = TOGLFWBUTTON(btn);
    return b >= 0 && b < BUTTON_COUNT && !m_curBtns[b] && m_prevBtns[b];
}

glm::dvec2 GLFWInput::ImplGetMousePosition() const {
    GLFWwindow* win = static_cast<GLFWwindow*>(Engine::GetInstance().GetWindow().GetNativeHandler());
    double x, y;
    glfwGetCursorPos(win, &x, &y);
    return {x, y};
}

} // namespace zui