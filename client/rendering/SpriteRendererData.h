#ifndef SPRITE_RENDERER_DATA_H
#define SPRITE_RENDERER_DATA_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "common/Vector2D.h"
#include "multimedia/SheetDataCache.h"
using std::string;

class SpriteRendererData {
public:
    string imageFile;
    string yamlFile;
    string rectId;

    Vector2D size;
    float angle;

    SpriteRendererData() {}

    SpriteRendererData(const string& imageFile, const string& yamlFile, const string& rectId,
                       Vector2D size = Vector2D::Zero(), float angle = 0) {
        this->imageFile = imageFile;
        this->yamlFile = yamlFile;
        this->rectId = rectId;
        this->size = size;
        this->angle = angle;
    }

    SDL2pp::Optional<Rect> GetSourceRect(int index = 0) const {
        if (yamlFile.empty())
            return SDL2pp::NullOpt;
        return SheetDataCache::GetData(yamlFile)[rectId][index];
    }

    virtual ~SpriteRendererData() = default;
};

#endif
