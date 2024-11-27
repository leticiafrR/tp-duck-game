#ifndef COLOR_EXTENSION_H
#define COLOR_EXTENSION_H
#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;  // NOLINT

class ColorExtension {
public:
    ColorExtension() = delete;
    ~ColorExtension() = delete;

    static Color White();
    static Color Black();
    static Color Empty();
    static Color Red();
    static Color Green();
    static Color Blue();
    static Color SkyBlue();
    static Color Purple();
    static Color Orange();
    static Color Cyan();
    static Color Yellow();

    static Color AddValue(Color color, int value);

    static Color Lerp(const Color& start, const Color& end, float t);
};

#endif
