#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "Camera.h"
#include "GraphicUI.h"
#include "RectTransform.h"
#include "SheetDataCache.h"

using namespace SDL2pp;  // NOLINT

class Image: public GraphicUI {
private:
    std::string filename = "";
    SDL2pp::Optional<Rect> srcRect = SDL2pp::NullOpt;
    bool flip = false;

public:
    explicit Image(const RectTransform& rect, Color color = Color(255, 255, 255),
                   int layerOrder = 0):
            GraphicUI(rect, color, layerOrder) {}

    Image(const std::string& filename, const RectTransform& rect,
          Color color = Color(255, 255, 255), int layerOrder = 0):
            GraphicUI(rect, color, layerOrder), filename(filename) {}
    ~Image() = default;

    void SetSourceRect(const string& filename, const string& key, int index = 0) {
        this->srcRect = SheetDataCache::GetData(filename)[key][index];
    }
    void SetSourceRect(const SDL2pp::Optional<Rect>& rect) { this->srcRect = rect; }

    void SetFile(const std::string& filename) { this->filename = filename; }

    void Draw(Camera& cam) override {
        if (filename.empty()) {
            cam.DrawGUI(rect, color);
        } else {
            cam.DrawImageGUI(filename, rect, srcRect, color, flip);
        }
    }

    void SetFlip(bool flip) { this->flip = flip; }
};

#endif
