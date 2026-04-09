#include "VertexBuffer.hpp"

#include "../Logger/Log.hpp"
#include "../Platform/Opengl/OpenglVertexBuffer.hpp"
#include "Renderer.hpp"


namespace zui {

std::shared_ptr<VertexBuffer> VertexBuffer::Create(const float* vertices, std::uint32_t size) {
    switch (Renderer::GetAPI()) {
    case GraphicsAPI::OPENGL:
        return std::make_shared<OpenglVertexBuffer>(vertices, size);
    default:
        LOGGER_ERROR("Unkown Renderer API");
        return nullptr;
    }
}

std::shared_ptr<IndexBuffer> IndexBuffer::Create(const std::uint32_t* indices, std::uint32_t count) {
    switch (Renderer::GetAPI()) {
    case GraphicsAPI::OPENGL:
        return std::make_shared<OpenglIndexBuffer>(indices, count);
    default:
        LOGGER_ERROR("Unkown Renderer API");
        return nullptr;
    }
}

} // namespace zui
