#pragma once

namespace zui {

struct Color {
    float R{0.0f}, G{0.0f}, B{0.0f}, A{1.0f};

    constexpr Color() noexcept = default;

    /**
     * @param r Color red value range 0.0-1.0.
     * @param g Color green value range 0.0-1.0.
     * @param b Color blue value range 0.0-1.0.
     * @param a Color alpha value range 0.0-1.0.
     */
    constexpr Color(float r, float g, float b, float a = 1.0f) noexcept : R(r), G(g), B(b), A(a) {}

    /**
     * @param r Color red value range 0-255.
     * @param g Color green value range 0-255.
     * @param b Color blue value range 0-255.
     * @param a Color alpha value range 0-255.
     */
    constexpr Color(int r, int g, int b, int a = 255) noexcept
        : R(static_cast<float>(r) / 255.0f), G(static_cast<float>(g) / 255.0f), B(static_cast<float>(b) / 255.0f),
          A(static_cast<float>(a) / 255.0f) {}
};

namespace colors {

inline constexpr Color BLACK{0, 0, 0};
inline constexpr Color WHITE{255, 255, 255};

inline constexpr Color RED{255, 0, 0};
inline constexpr Color GREEN{0, 255, 0};
inline constexpr Color BLUE{0, 0, 255};

inline constexpr Color YELLOW{255, 255, 0};
inline constexpr Color CYAN{0, 255, 255};
inline constexpr Color MAGENTA{255, 0, 255};

inline constexpr Color GRAY{128, 128, 128};
inline constexpr Color LIGHT_GRAY{211, 211, 211};
inline constexpr Color DARK_GRAY{64, 64, 64};

inline constexpr Color ORANGE{255, 165, 0};
inline constexpr Color PURPLE{128, 0, 128};
inline constexpr Color PINK{255, 192, 203};
inline constexpr Color BROWN{165, 42, 42};
inline constexpr Color LIME{50, 205, 50};
inline constexpr Color NAVY{0, 0, 128};
inline constexpr Color TEAL{0, 128, 128};
inline constexpr Color OLIVE{128, 128, 0};
inline constexpr Color MAROON{128, 0, 0};
inline constexpr Color SILVER{192, 192, 192};
inline constexpr Color GOLD{255, 215, 0};

inline constexpr Color SKY_BLUE{135, 206, 235};
inline constexpr Color CORNFLOWER_BLUE{100, 149, 237};
inline constexpr Color ROYAL_BLUE{65, 105, 225};
inline constexpr Color FOREST_GREEN{34, 139, 34};
inline constexpr Color SPRING_GREEN{0, 255, 127};
inline constexpr Color TURQUOISE{64, 224, 208};
inline constexpr Color VIOLET{238, 130, 238};
inline constexpr Color INDIGO{75, 0, 130};
inline constexpr Color KHAKI{240, 230, 140};
inline constexpr Color SALMON{250, 128, 114};
inline constexpr Color CRIMSON{220, 20, 60};

} // namespace colors

namespace literals {

constexpr Color operator""_rgb(unsigned long long hex) {
    return Color{static_cast<int>((hex >> 16) & 0xFF), static_cast<int>((hex >> 8) & 0xFF),
                 static_cast<int>(hex & 0xFF)};
}

constexpr Color operator""_rgba(unsigned long long hex) {
    return Color{static_cast<int>((hex >> 24) & 0xFF), static_cast<int>((hex >> 16) & 0xFF),
                 static_cast<int>((hex >> 8) & 0xFF), static_cast<int>(hex & 0xFF)};
}

} // namespace literals

} // namespace zui
