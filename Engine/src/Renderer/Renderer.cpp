#include "Renderer.hpp"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace zui {

Renderer::Renderer(RenderMode mode) : m_renderMode(mode), m_clearColor{}, m_renderClearFlags(GL_COLOR_BUFFER_BIT) {
    int version = gladLoadGL(glfwGetProcAddress);

    if (version == 0) {
        // log error
        return;
    }

    glEnable(GL_BLEND);

    SetRenderMode(mode);
}
Renderer::~Renderer() {}

void Renderer::SetRenderMode(RenderMode mode) {
    m_renderMode = mode;
    if (mode == RenderMode::RENDER_2D) {
        m_renderClearFlags &= ~GL_DEPTH_BUFFER_BIT;
        glDisable(GL_DEPTH_TEST);
    } else if (mode == RenderMode::RENDER_3D) {
        m_renderClearFlags |= GL_DEPTH_BUFFER_BIT;
        glEnable(GL_DEPTH_TEST);
    }
}

RenderMode Renderer::GetRenderMode() const {
    return m_renderMode;
}

void Renderer::Clear() const {
    glClear(m_renderClearFlags);
}

void Renderer::SetClearColor(const Color& color) {
    m_clearColor = color;
    glClearColor(m_clearColor.R, m_clearColor.G, m_clearColor.B, m_clearColor.A);
}

} // namespace zui
