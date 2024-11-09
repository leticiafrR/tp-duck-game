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
    static Color Yellow() { return Color(255, 0, 255); }

    static Color AddValue(Color color, int value) {
        return Color(std::clamp(color.r + value, 0, 255), std::clamp(color.g + value, 0, 255),
                     std::clamp(color.b + value, 0, 255));
    }

    ColorExtension() = delete;
    ~ColorExtension() = delete;
};

#endif
