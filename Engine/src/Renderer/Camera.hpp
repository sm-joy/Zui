#pragma once
#include "../Core/API.hpp"
#include <glm/glm.hpp>

namespace zui {
    
class ZUI_API Camera {
public:
    virtual ~Camera() = default;

    virtual const glm::mat4& GetViewMatrix() const = 0;
    virtual const glm::mat4& GetProjectionMatrix() const = 0;
    virtual const glm::mat4& GetViewProjectionMatrix() const = 0;
    virtual const glm::vec3& GetPosition() const = 0;
};

class ZUI_API PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(float fov, float aspect, float nearClip, float farClip);

    void SetPosition(const glm::vec3& p) {
        m_position = p;
        RecalcView();
    }
    void SetFront(const glm::vec3& f) {
        m_front = f;
        RecalcView();
    }
    void SetUp(const glm::vec3& u) {
        m_up = u;
        RecalcView();
    }
    void SetProjection(float fov, float aspect, float nearClip, float farClip);

    const glm::vec3& GetPosition() const override { return m_position; }
    const glm::vec3& GetFront() const { return m_front; }
    const glm::vec3& GetUp() const { return m_up; }
    const glm::mat4& GetViewMatrix() const override { return m_view; }
    const glm::mat4& GetProjectionMatrix() const override { return m_projection; }
    const glm::mat4& GetViewProjectionMatrix() const override { return m_viewProjection; }

private:
    void RecalcView();
    glm::mat4 m_projection = glm::mat4(1.0f);
    glm::mat4 m_view, m_viewProjection;
    glm::vec3 m_position = {0.0f, 0.0f, 3.0f};
    glm::vec3 m_front = {0.0f, 0.0f, -1.0f};
    glm::vec3 m_up = {0.0f, 1.0f, 0.0f};
};

} // namespace zui