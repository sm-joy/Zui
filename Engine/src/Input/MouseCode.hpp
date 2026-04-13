#pragma once
#include <cstdint>

namespace zui {

enum class MouseCode : uint8_t {
    BUTTON0 = 0,
    BUTTON1 = 1,
    BUTTON2 = 2,
    BUTTON3 = 3,
    BUTTON4 = 4,
    BUTTON5 = 5,
    BUTTON6 = 6,
    BUTTON7 = 7,

    LEFT = BUTTON0,
    RIGHT = BUTTON1,
    MIDDLE = BUTTON2,
};

}