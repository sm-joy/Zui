#pragma once
#include "../Values/Color.hpp"

#include <cstdint>

namespace zui {

enum class RenderMode : std::uint8_t { RENDER_2D, RENDER_3D };

class Renderer {
public:
    Renderer(RenderMode mode = RenderMode::RENDER_2D);
    ~Renderer();

    RenderMode GetRenderMode() const;
    void Clear() const;
    void SetRenderMode(RenderMode mode);
    void SetClearColor(const Color& color);

private:
    RenderMode m_renderMode;
    unsigned int m_renderClearFlags;
    Color m_clearColor;
};

} // namespace zui
