#include "../Logger/Log.hpp"
#include "../Platform/Opengl/OpenglContext.hpp"
#include "GraphicsContext.hpp"
#include "RendererAPI.hpp"

#include <GLFW/glfw3.h>

namespace zui {

std::unique_ptr<GraphicsContext> GraphicsContext::Create(void* window) {
    if (!window) {
        LOGGER_CRITICAL("GraphicsContext::Create received a null window handle.");
        return nullptr;
    }

    switch (RendererAPI::GetGraphicsAPI()) {
    case GraphicsAPI::OPENGL:
        return std::make_unique<OpenglContext>(static_cast<GLFWwindow*>(window));
    case GraphicsAPI::NONE:
    case GraphicsAPI::VULKAN:
    default:
        LOGGER_CRITICAL("Unkwon API, Could not load api!");
        return nullptr;
    }
}

} // namespace zui
