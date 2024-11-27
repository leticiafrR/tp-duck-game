#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "multimedia/Camera.h"
#include "multimedia/cache/SheetDataCache.h"

#include "GraphicUI.h"
#include "RectTransform.h"

using namespace SDL2pp;  // NOLINT

class Image: public GraphicUI {
private:
    std::string filename = "";
    SDL2pp::Optional<Rect> srcRect = SDL2pp::NullOpt;
    bool flip = false;

public:
    explicit Image(const RectTransform& rect, Color color = Color(255, 255, 255),
                   int layerOrder = 0);

    Image(const std::string& filename, const RectTransform& rect,
          Color color = Color(255, 255, 255), int layerOrder = 0);
    ~Image();

    void SetSourceRect(const string& filename, const string& key, int index = 0);
    void SetSourceRect(const SDL2pp::Optional<Rect>& rect);

    void SetFile(const std::string& filename);

    void Draw(Camera& cam) override;

    void SetFlip(bool flip);
};

#endif
