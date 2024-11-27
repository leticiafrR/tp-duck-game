#include "SpriteRendererData.h"

SpriteRendererData::SpriteRendererData() {}
SpriteRendererData::~SpriteRendererData() = default;

SpriteRendererData::SpriteRendererData(const string& imageFile, const string& yamlFile,
                                       const string& rectId, Vector2D size, float angle) {
    this->imageFile = imageFile;
    this->yamlFile = yamlFile;
    this->rectId = rectId;
    this->size = size;
    this->angle = angle;
}

SDL2pp::Optional<Rect> SpriteRendererData::GetSourceRect(int index) const {
    if (yamlFile.empty())
        return SDL2pp::NullOpt;
    return SheetDataCache::GetData(yamlFile)[rectId][index];
}
