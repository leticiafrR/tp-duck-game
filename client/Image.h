#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "Camera.h"
#include "GraphicUI.h"
#include "RectTransform.h"

using namespace SDL2pp;  // NOLINT

class Image: public GraphicUI {
private:
    std::string filename = "";
    SDL2pp::Optional<Rect> srcRect = SDL2pp::NullOpt;
    Color color;

public:
    explicit Image(const RectTransform& rect, Color color = Color(255, 255, 255),
                   int layerOrder = 0):
            GraphicUI(rect, layerOrder), color(color) {}

    Image(const std::string& filename, const RectTransform& rect,
          Color color = Color(255, 255, 255), int layerOrder = 0):
            GraphicUI(rect, layerOrder), filename(filename), color(color) {}
    ~Image() = default;

    void SetColor(Color color) { this->color = color; }
    Color GetColor() { return color; }

    void SetSourceRect(const SDL2pp::Optional<Rect>& rect) { this->srcRect = rect; }

    void Draw(Camera& cam) override {
        if (filename.empty()) {
            cam.DrawGUI(rect, color);
        } else {
            cam.DrawImageGUI(filename, rect, srcRect, color);
        }
    }
};

#endif
