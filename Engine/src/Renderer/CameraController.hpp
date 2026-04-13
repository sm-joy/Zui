#pragma once
#include "Camera.hpp"
#include "../Core/API.hpp"

namespace zui {

class Event;

class ZUI_API PerspectiveCameraController {
public:
    PerspectiveCameraController(float aspectRatio, float fov = 45.0f, float nearClip = 0.1f, float farClip = 1000.0f);

    void OnUpdate(float dt);
    void OnEvent(Event& e);

    PerspectiveCamera& GetCamera() { return m_camera; }
    const PerspectiveCamera& GetCamera() const { return m_camera; }

    void SetMouseLookEnabled(bool enabled) { m_mouseLookEnabled = enabled; }
    bool GetMouseLookEnabled() const { return m_mouseLookEnabled; }

    void SetMoveSpeed(float s) { m_moveSpeed = s; }
    void SetMouseSensitivity(float s) { m_sensitivity = s; }

private:

    void UpdateProjection();

    PerspectiveCamera m_camera;

    float m_aspectRatio;
    float m_fov = 45.0f;
    float m_nearClip = 0.1f;
    float m_farClip = 1000.0f;

    glm::vec3 m_position = {0.0f, 0.0f, 3.0f};
    float m_moveSpeed = 2.5f;


    float m_yaw = -90.0f;
    float m_pitch = 0.0f;
    float m_sensitivity = 0.1f;
    float m_lastX = 0.0f;
    float m_lastY = 0.0f;
    bool m_firstMouse = true;
    bool m_mouseLookEnabled = true;
    bool m_mouseLocked = false;
};

} // namespace zui