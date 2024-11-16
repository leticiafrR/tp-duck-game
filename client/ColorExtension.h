#ifndef COLOR_EXTENSION_H
#define COLOR_EXTENSION_H
#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;  // NOLINT

class ColorExtension {
private:
public:
    static Color White() { return Color(255, 255, 255); }
    static Color Black() { return Color(0, 0, 0); }
    static Color Red() { return Color(255, 0, 0); }
    static Color Green() { return Color(0, 255, 0); }
    static Color Blue() { return Color(0, 0, 255); }
    static Color SkyBlue() { return Color(135, 206, 250); }
    static Color Purple() { return Color(128, 0, 128); }
    static Color Orange() { return Color(255, 165, 128); }
    static Color Cyan() { return Color(0, 255, 255); }
    static Color Yellow() { return Color(255, 255, 0); }

    static Color AddValue(Color color, int value) {
        return Color(std::clamp(color.r + value, 0, 255), std::clamp(color.g + value, 0, 255),
                     std::clamp(color.b + value, 0, 255));
    }

    static Color Lerp(const Color& start, const Color& end, float t) {
        t = std::clamp(t, 0.0f, 1.0f);
        return Color(start.r + (end.r - start.r) * t, start.g + (end.g - start.g) * t,
                     start.b + (end.b - start.b) * t, start.a + (end.a - start.a) * t);
    }

    ColorExtension() = delete;
    ~ColorExtension() = delete;
};

#endif
