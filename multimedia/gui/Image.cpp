#include "Image.h"

Image::Image(const RectTransform& rect, Color color, int layerOrder):
        GraphicUI(rect, color, layerOrder) {}

Image::Image(const std::string& filename, const RectTransform& rect, Color color, int layerOrder):
        GraphicUI(rect, color, layerOrder), filename(filename) {}

Image::~Image() = default;

void Image::SetSourceRect(const SDL2pp::Optional<Rect>& rect) { this->srcRect = rect; }

void Image::SetFile(const std::string& filename) { this->filename = filename; }

void Image::Draw(Camera& cam) {
    if (filename.empty()) {
        cam.DrawGUI(rect, color);
    } else {
        cam.DrawImageGUI(filename, rect, srcRect, color, flip);
    }
}

void Image::SetFlip(bool flip) { this->flip = flip; }
