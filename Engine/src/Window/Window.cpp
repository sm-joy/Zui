#include "Window.hpp"

#include "../Event/Event.hpp"
#include "../Logger/Log.hpp"
#include "../Renderer/GraphicsContext.hpp"
#include "../Renderer/Renderer.hpp"

#include <GLFW/glfw3.h>

namespace zui {

Window::Window(const WinConfig& winConfig) : m_winConfig(winConfig) {}

Window::~Window() {
    DestroyWindow();
}

bool Window::CreateNativeWindow() {
    if (!m_winConfig.Title) {
        LOGGER_ERROR("Window title cannot be null.");
        return false;
    }

    if (m_winConfig.Width <= 0 || m_winConfig.Height <= 0) {
        LOGGER_ERROR("Window size must be positive.");
        return false;
    }

    if (!m_glfwInitialized) {
        if (!glfwInit()) {
            LOGGER_CRITICAL("Failed to initialize GLFW.");
            return false;
        }

        m_glfwInitialized = true;
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
        LOGGER_CRITICAL("Failed to create GLFW window.");
        return false;
    }

    m_graphicsContext = GraphicsContext::Create(m_windowHandle);
    if (!m_graphicsContext) {
        LOGGER_CRITICAL("Failed to create graphics context.");
        DestroyWindow();
        return false;
    }

    m_graphicsContext->Init();

    glfwSetWindowUserPointer(m_windowHandle, this);
    glfwSwapInterval(m_winConfig.Vsync);
    SetGlfwCallbacks();
    Renderer::OnWindowResize(m_winConfig.Width, m_winConfig.Height);

    return true;
}

void Window::DestroyWindow() {
    m_graphicsContext.reset();

    if (m_windowHandle) {
        glfwDestroyWindow(m_windowHandle);
        m_windowHandle = nullptr;
    }

    if (m_glfwInitialized) {
        glfwTerminate();
        m_glfwInitialized = false;
    }
}

void Window::UpdateConfig(const WinConfig& winCfg) {
    m_winConfig = winCfg;

    if (!m_windowHandle) {
        CreateNativeWindow();
        return;
    }

    glfwSetWindowTitle(m_windowHandle, m_winConfig.Title);
    glfwSetWindowSize(m_windowHandle, m_winConfig.Width, m_winConfig.Height);
    glfwSwapInterval(m_winConfig.Vsync);
    glfwSetWindowAttrib(m_windowHandle, GLFW_RESIZABLE, m_winConfig.Resizable ? GLFW_TRUE : GLFW_FALSE);
    Renderer::OnWindowResize(m_winConfig.Width, m_winConfig.Height);
}

void Window::Update() const {
    if (!m_windowHandle || !m_graphicsContext) {
        return;
    }

    glfwPollEvents();
    m_graphicsContext->SwapBuffers();
}

GLFWwindow* Window::GetWindowHandle() const {
    return m_windowHandle;
}

bool Window::ShouldClose() const {
    if (!m_windowHandle) {
        return true;
    }

    return glfwWindowShouldClose(m_windowHandle);
}

void Window::SetGlfwCallbacks() {
    glfwSetFramebufferSizeCallback(m_windowHandle, [](GLFWwindow* glfwWindow, int width, int height) {
        Window& window = *((Window*)glfwGetWindowUserPointer(glfwWindow));
        window.m_winConfig.Width = width;
        window.m_winConfig.Height = height;
        Renderer::OnWindowResize(width, height);
    });

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
        window.m_winConfig.Width = width;
        window.m_winConfig.Height = height;

        WindowResizeEvent event(width, height);
        window.m_winConfig.EventEmitCallback(event);
    });
}

} // namespace zui
