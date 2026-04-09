#include "VertexArray.hpp"
#include "../Logger/Log.hpp"
#include "Renderer.hpp"
#include "../Platform/Opengl/OpenglVertexArray.hpp"

namespace zui {

std::shared_ptr<VertexArray> VertexArray::Create() {
    switch (Renderer::GetAPI()) {
        case GraphicsAPI::OPENGL:
            return std::make_shared<OpenglVertexArray>();
        default:
            LOGGER_ERROR("Unknown RendererAPI");
            return nullptr;
    }
}

} // namespace zui
