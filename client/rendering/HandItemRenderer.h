#ifndef HAND_ITEM_RENDERER_H
#define HAND_ITEM_RENDERER_H
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "common/Transform.h"
#include "data/snapshot.h"
#include "multimedia/2d/Object2D.h"
#include "multimedia/cache/SheetDataCache.h"
#include "multimedia/resource/ResourceData.h"

#include "SpriteRendererData.h"

using std::string;
using std::unordered_map;

class HandItemRenderer: public Object2D {
private:
    Transform& playerT;
    float angle;
    const Vector2D offset = Vector2D(0, -0.4f);

public:
    explicit HandItemRenderer(Transform& playerT, CollectableData data = CollectableData());
    ~HandItemRenderer();

    void SetItem(CollectableData type);

    void Update(bool playerFlip, bool lookingUp);
};

#endif
