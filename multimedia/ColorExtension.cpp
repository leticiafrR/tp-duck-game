#include "ColorExtension.h"

Color ColorExtension::White() { return Color(255, 255, 255); }
Color ColorExtension::Black() { return Color(0, 0, 0); }
Color ColorExtension::Empty() { return Color(0, 0, 0, 0); }
Color ColorExtension::Red() { return Color(255, 0, 0); }
Color ColorExtension::Green() { return Color(0, 255, 0); }
Color ColorExtension::Blue() { return Color(0, 0, 255); }
Color ColorExtension::SkyBlue() { return Color(135, 206, 250); }
Color ColorExtension::Purple() { return Color(128, 0, 128); }
Color ColorExtension::Orange() { return Color(255, 165, 128); }
Color ColorExtension::Cyan() { return Color(0, 255, 255); }
Color ColorExtension::Yellow() { return Color(255, 255, 0); }

Color ColorExtension::AddValue(Color color, int value) {
    return Color(std::clamp(color.r + value, 0, 255), std::clamp(color.g + value, 0, 255),
                 std::clamp(color.b + value, 0, 255));
}

Color ColorExtension::Lerp(const Color& start, const Color& end, float t) {
    t = std::clamp(t, 0.0f, 1.0f);
    return Color(start.r + (end.r - start.r) * t, start.g + (end.g - start.g) * t,
                 start.b + (end.b - start.b) * t, start.a + (end.a - start.a) * t);
}
