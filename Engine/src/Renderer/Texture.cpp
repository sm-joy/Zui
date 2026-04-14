#include "Texture.hpp"
#include "Renderer.hpp"
#include "../Platform/Opengl/OpenglTexture.hpp"
#include "../Logger/Log.hpp"

namespace zui {
std::shared_ptr<Texture2D> Texture2D::Create(const std::string& filepath) {
    switch (Renderer::GetAPI()) {
    case GraphicsAPI::OPENGL:
        return std::make_shared<OpenglTexture2D>(filepath);
    default: {
        LOGGER_ERROR("Unknown RendererAPI");
        return nullptr;
    }
    }
}

std::shared_ptr<Texture2D> Texture2D::Create(int width, int height) {
    switch (Renderer::GetAPI()) {
    case GraphicsAPI::OPENGL:
        return std::make_shared<OpenglTexture2D>(width, height);
    default: {
        LOGGER_ERROR("Unknown RendererAPI");
        return nullptr;
    }
    }
}
}