#include "Window.hpp"

#include <GLFW/glfw3.h>

namespace zui {

Window::Window(const WinConfig& winConfig) : m_window(nullptr), m_winConfig(winConfig) {
    if (!m_winConfig.Title)
        return;
    if (!(m_winConfig.Height > 0 && m_winConfig.Width > 0))
        return;

    if (!glfwInit()) {
        // log
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, m_winConfig.Resizable);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
#endif

    m_window = glfwCreateWindow(m_winConfig.Width, m_winConfig.Height, m_winConfig.Title, nullptr, nullptr);
    if (!m_window) {
        // log
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_window);
    glViewport(0, 0, m_winConfig.Width, m_winConfig.Height);
    glfwSetWindowUserPointer(m_window, this);

    if (m_winConfig.Mode == WindowMode::FULLSCREEN)
        glfwMaximizeWindow(m_window);
    glfwSwapInterval(m_winConfig.Vsync);
}

Window::~Window() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Window::UpdateConfig(const WinConfig& winCfg) {
    glfwSetWindowTitle(m_window, winCfg.Title);

    glfwSetWindowSize(m_window, winCfg.Width, winCfg.Height);
    glfwSwapInterval(winCfg.Vsync);

    if (winCfg.Resizable != m_winConfig.Resizable) {
        // i'll chack this out later
    }

    m_winConfig = winCfg;
}

void Window::Update() const {
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}

GLFWwindow* Window::GetWindowHandle() const {
    return m_window;
}

bool Window::ShouldClose() const {
    return glfwWindowShouldClose(m_window);
}

} // namespace zui
