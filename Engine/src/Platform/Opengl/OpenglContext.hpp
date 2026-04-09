#include "../../Renderer/GraphicsContext.hpp"

struct GLFWwindow;

namespace zui {

class OpenglContext : public GraphicsContext {
public:
    OpenglContext(GLFWwindow* windowHandle);

    void Init() override;
    void SwapBuffers() override;

private:
    GLFWwindow* m_windowHandle = nullptr;
};

} // namespace zui
