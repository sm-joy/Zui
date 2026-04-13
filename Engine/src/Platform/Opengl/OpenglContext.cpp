#include "OpenglContext.hpp"
#include "../../Logger/Log.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>


namespace zui {

OpenglContext::OpenglContext(GLFWwindow* windowHandle) : m_windowHandle(windowHandle) {}

void OpenglContext::Init() {
    glfwMakeContextCurrent(m_windowHandle);
    int version = gladLoadGL(glfwGetProcAddress);

    if (version == 0) {
        LOGGER_ERROR("Error loading opengl functions");
        return;
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenglContext::SwapBuffers() {
    glfwSwapBuffers(m_windowHandle);
}

} // namespace zui
