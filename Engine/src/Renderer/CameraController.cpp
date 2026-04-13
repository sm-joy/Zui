#include "CameraController.hpp"

#include "../Event/Event.hpp"
#include "../Input/Input.hpp"
#include "../Core/Engine.hpp"

namespace zui {

PerspectiveCameraController::PerspectiveCameraController(float aspectRatio, float fov, float nearClip, float farClip)
    : m_camera(fov, aspectRatio, nearClip, farClip), m_aspectRatio(aspectRatio), m_fov(fov), m_nearClip(nearClip),
      m_farClip(farClip) {
    glm::vec2 mousePos = static_cast<glm::vec2>(Input::GetMousePosition());
    m_lastX = mousePos.x;
    m_lastY = mousePos.y;
}

void PerspectiveCameraController::OnUpdate(float dt) {

    if (Input::IsKeyDown(zui::KeyCode::E)) {
        m_mouseLocked = !m_mouseLocked;
        m_firstMouse  = true;

        if (m_mouseLocked) {
            Engine::GetInstance().GetWindow().HideCursor();
        }
        else {
            Engine::GetInstance().GetWindow().ShowCursor();
        }
    }

    glm::vec3 front = m_camera.GetFront();
    glm::vec3 up    = m_camera.GetUp();
    glm::vec3 right = glm::normalize(glm::cross(front, up));

    if (Input::IsKeyPressed(zui::KeyCode::W))          m_position += front * m_moveSpeed * dt;
    if (Input::IsKeyPressed(zui::KeyCode::S))          m_position -= front * m_moveSpeed * dt;
    if (Input::IsKeyPressed(zui::KeyCode::A))          m_position -= right * m_moveSpeed * dt;
    if (Input::IsKeyPressed(zui::KeyCode::D))          m_position += right * m_moveSpeed * dt;
    if (Input::IsKeyPressed(zui::KeyCode::SPACE))      m_position += up * m_moveSpeed * dt;
    if (Input::IsKeyPressed(zui::KeyCode::LEFT_SHIFT)) m_position -= up * m_moveSpeed * dt;

    float speedMul = Input::IsKeyPressed(zui::KeyCode::LEFT_ALT) ? 3.0f : 1.0f;
    m_position += (front * m_moveSpeed * dt) * (speedMul - 1.0f)
                  * (float)(Input::IsKeyPressed(zui::KeyCode::W) - Input::IsKeyPressed(zui::KeyCode::S));

    m_camera.SetPosition(m_position);

    if (!m_mouseLookEnabled || !m_mouseLocked) {
        m_firstMouse = true;
        return;
    }

    glm::vec2 mousePos = static_cast<glm::vec2>(Input::GetMousePosition());

    if (m_firstMouse) {
        m_lastX      = mousePos.x;
        m_lastY      = mousePos.y;
        m_firstMouse = false;
        return;
    }

    float offsetX = (mousePos.x - m_lastX) * m_sensitivity;
    float offsetY = (m_lastY - mousePos.y) * m_sensitivity;
    m_lastX = mousePos.x;
    m_lastY = mousePos.y;

    m_yaw   += offsetX;
    m_pitch += offsetY;
    m_pitch  = glm::clamp(m_pitch, -89.0f, 89.0f);

    glm::vec3 newFront;
    newFront.x = glm::cos(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
    newFront.y = glm::sin(glm::radians(m_pitch));
    newFront.z = glm::sin(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));

    m_camera.SetFront(glm::normalize(newFront));
}

void PerspectiveCameraController::OnEvent(Event& e) {
    Dispatch(e)
        .On<WindowResizeEvent>([this](WindowResizeEvent& e) {
            m_aspectRatio = static_cast<float>(e.GetWidth()) / static_cast<float>(e.GetHeight());
            UpdateProjection();
            return false;
        })
        .On<MouseScrolledEvent>([this](MouseScrolledEvent& e) {
            m_fov -= static_cast<float>(e.GetYOffset()) * 2.0f;
            m_fov = glm::clamp(m_fov, 10.0f, 90.0f);
            UpdateProjection();
            return false;
        });
}

void PerspectiveCameraController::UpdateProjection() {
    m_camera.SetProjection(m_fov, m_aspectRatio, m_nearClip, m_farClip);
}


} // namespace zui