#pragma once
#include <cstdint>

namespace zui {

enum class GraphicsAPI : std::uint8_t { NONE = 0, OPENGL, VULKAN, COUNT };

} // namespace zui
