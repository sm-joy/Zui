#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>


namespace zui {
PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float nearClip, float farClip) {
    m_projection = glm::perspective(glm::radians(fov), aspect, nearClip, farClip);
    RecalcView();
}

void PerspectiveCamera::SetProjection(float fov, float aspect, float nearClip, float farClip) {
    m_projection = glm::perspective(glm::radians(fov), aspect, nearClip, farClip);
    m_viewProjection = m_projection * m_view;
}

void PerspectiveCamera::RecalcView() {
    m_view = glm::lookAt(m_position, m_position + m_front, m_up);
    m_viewProjection = m_projection * m_view;
}

} // namespace zui