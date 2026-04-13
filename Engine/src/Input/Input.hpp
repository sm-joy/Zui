#pragma once
#include "KeyCode.hpp"
#include "MouseCode.hpp"
#include "../Core/API.hpp"

#include <glm/glm.hpp>
#include <memory>


namespace zui {

class ZUI_API Input {
public:
    virtual ~Input() = default;

    static inline bool IsKeyPressed(KeyCode k) { return s_instance->ImplIsKeyPressed(k); }
    static inline bool IsKeyDown(KeyCode k) { return s_instance->ImplIsKeyDown(k); }
    static inline bool IsKeyReleased(KeyCode k) { return s_instance->ImplIsKeyReleased(k); }
    static inline bool IsMouseButtonPressed(MouseCode b) { return s_instance->ImplIsMouseButtonPressed(b); }
    static inline bool IsMouseButtonDown(MouseCode b) { return s_instance->ImplIsMouseButtonDown(b); }
    static inline bool IsMouseButtonReleased(MouseCode b) { return s_instance->ImplIsMouseButtonReleased(b); }
    static inline double GetMouseX() { return s_instance->ImplGetMousePosition().x; }
    static inline double GetMouseY() { return s_instance->ImplGetMousePosition().y; }
    static inline glm::dvec2 GetMousePosition() { return s_instance->ImplGetMousePosition(); }

private:
    friend class Engine;
    static std::unique_ptr<Input> s_instance;

    static inline void Init();
    static inline void Shutdown();
    static inline void OnUpdate();

protected:
    virtual bool ImplIsKeyPressed(KeyCode key) const = 0;
    virtual bool ImplIsKeyDown(KeyCode key) const = 0;
    virtual bool ImplIsKeyReleased(KeyCode key) const = 0;
    virtual bool ImplIsMouseButtonPressed(MouseCode b) const = 0;
    virtual bool ImplIsMouseButtonDown(MouseCode b) const = 0;
    virtual bool ImplIsMouseButtonReleased(MouseCode b) const = 0;
    virtual glm::dvec2 ImplGetMousePosition() const = 0;

    virtual void ImplOnUpdate() = 0;
};

} // namespace zui