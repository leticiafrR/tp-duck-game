#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "Camera.h"
#include "RectTransform.h"

using namespace SDL2pp;  // NOLINT

class Image {
private:
    RectTransform rect;
    Color color;
    int layer;

public:
    explicit Image(RectTransform rect, Color color = Color(255, 255, 255), int layer = 0):
            rect(rect), color(color), layer(layer) {}
    ~Image() = default;

    RectTransform& GetRectTransform() { return rect; }

    void SetColor(Color color) { this->color = color; }

    void Draw(Camera& cam) { cam.DrawGUI(rect, color); }
};

#endif
