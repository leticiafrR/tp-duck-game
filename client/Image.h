#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "Camera.h"
#include "GraphicUI.h"
#include "RectTransform.h"

using namespace SDL2pp;  // NOLINT

class Image: public GraphicUI {
private:
    RectTransform rect;
    Color color;

public:
    explicit Image(RectTransform rect, Color color = Color(255, 255, 255), int layerOrder = 0):
            GraphicUI(layerOrder), rect(rect), color(color) {}
    ~Image() = default;

    RectTransform& GetRectTransform() { return rect; }

    void SetColor(Color color) { this->color = color; }

    void Draw(Camera& cam) override { cam.DrawGUI(rect, color); }
};

#endif
