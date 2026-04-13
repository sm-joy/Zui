#pragma once
#include "API.hpp"

namespace zui {
class ZUI_API EngineContext {
public:
    inline void HideCursor() const;
    inline void ShowCursor() const;

    inline int GetWindowWidth() const;
    inline int GetWindowHeight() const;
};
}