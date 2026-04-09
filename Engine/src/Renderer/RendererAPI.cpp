#include "RendererAPI.hpp"

#include "../Logger/Log.hpp"
#include "../Platform/Opengl/OpenglRendererAPI.hpp"
#include "RendererConfig.hpp"


namespace zui {
GraphicsAPI RendererAPI::s_api = GraphicsAPI::OPENGL;

std::unique_ptr<RendererAPI> RendererAPI::Create() {
    switch (s_api) {
    case GraphicsAPI::NONE:
        LOGGER_ERROR("GraphicsAPI::None is currently not supported! Falling back to default!");
        break;
    case GraphicsAPI::OPENGL:
        break;
    case GraphicsAPI::VULKAN:
        LOGGER_ERROR("GraphicsAPI::VULKAN is currently not supported! Falling back to default!");
        break;
    case GraphicsAPI::COUNT:
    default:
        LOGGER_ERROR("Invalid GraphicsAPI value! Falling back to default!");
        break;
    }

    return std::make_unique<OpenglRendererAPI>();
}
} // namespace zui
