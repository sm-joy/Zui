#include "Window.hpp"

#include "../Event/Event.hpp"

#include <GLFW/glfw3.h>

namespace zui {

Window::Window(const WinConfig& winConfig) : m_windowHandle(nullptr), m_winConfig(winConfig) {
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

    m_windowHandle = glfwCreateWindow(m_winConfig.Width, m_winConfig.Height, m_winConfig.Title, nullptr, nullptr);
    if (!m_windowHandle) {
        // log
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_windowHandle);
    glViewport(0, 0, m_winConfig.Width, m_winConfig.Height);
    glfwSetWindowUserPointer(m_windowHandle, this);

    if (m_winConfig.Mode == WindowMode::FULLSCREEN)
        glfwMaximizeWindow(m_windowHandle);

    glfwSwapInterval(m_winConfig.Vsync);
    SetGlfwCallbacks();
}

Window::~Window() {
    glfwDestroyWindow(m_windowHandle);
    glfwTerminate();
}

void Window::UpdateConfig(const WinConfig& winCfg) {
    glfwSetWindowTitle(m_windowHandle, winCfg.Title);

    glfwSetWindowSize(m_windowHandle, winCfg.Width, winCfg.Height);
    glfwSwapInterval(winCfg.Vsync);

    if (winCfg.Resizable != m_winConfig.Resizable) {
        // i'll chack this out later
    }

    m_winConfig = winCfg;
}

void Window::Update() const {
    glfwPollEvents();
    glfwSwapBuffers(m_windowHandle);
}

GLFWwindow* Window::GetWindowHandle() const {
    return m_windowHandle;
}

bool Window::ShouldClose() const {
    return glfwWindowShouldClose(m_windowHandle);
}

void Window::SetGlfwCallbacks() {
    glfwSetFramebufferSizeCallback(
        m_windowHandle, [](GLFWwindow* glfwWindow, int width, int height) { glViewport(0, 0, width, height); });

    glfwSetCursorPosCallback(m_windowHandle, [](GLFWwindow* glfwWindow, double xPos, double yPos) {
        Window& window = *((Window*)glfwGetWindowUserPointer(glfwWindow));

        MouseMovedEvent event(xPos, yPos);
        window.m_winConfig.EventEmitCallback(event);
    });

    glfwSetWindowCloseCallback(m_windowHandle, [](GLFWwindow* glfwWindow) {
        Window& window = *((Window*)glfwGetWindowUserPointer(glfwWindow));

        WindowCloseEvent event;
        window.m_winConfig.EventEmitCallback(event);
    });

    glfwSetMouseButtonCallback(m_windowHandle, [](GLFWwindow* glfwWindow, int button, int action, int mods) {
        Window& window = *((Window*)glfwGetWindowUserPointer(glfwWindow));

        switch (action) {
        case GLFW_PRESS: {
            MouseButtonPressedEvent event(button);
            window.m_winConfig.EventEmitCallback(event);
            break;
        }
        case GLFW_RELEASE: {
            MouseButtonReleasedEvent event(button);
            window.m_winConfig.EventEmitCallback(event);
            break;
        }
        default:
            break;
        }
    });

    glfwSetKeyCallback(m_windowHandle, [](GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
        Window& window = *((Window*)glfwGetWindowUserPointer(glfwWindow));
        switch (action) {
        case GLFW_PRESS:
        case GLFW_REPEAT: {
            KeyPressedEvent event(key, action == GLFW_REPEAT);
            window.m_winConfig.EventEmitCallback(event);
        } break;
        case GLFW_RELEASE: {
            KeyReleasedEvent event(key);
            window.m_winConfig.EventEmitCallback(event);
            break;
        }
        default:
            break;
        }
    });

    glfwSetScrollCallback(m_windowHandle, [](GLFWwindow* glfwWindow, double xOffset, double yOffset) {
        Window& window = *((Window*)glfwGetWindowUserPointer(glfwWindow));

        MouseScrolledEvent event(xOffset, yOffset);
        window.m_winConfig.EventEmitCallback(event);
    });

    glfwSetWindowSizeCallback(m_windowHandle, [](GLFWwindow* glfwWindow, int width, int height) {
        Window& window = *((Window*)glfwGetWindowUserPointer(glfwWindow));

        WindowResizeEvent event(width, height);
        window.m_winConfig.EventEmitCallback(event);
    });
}
} // namespace zui
