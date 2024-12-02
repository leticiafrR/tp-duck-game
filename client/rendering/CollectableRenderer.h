#ifndef COLLECTABLE_RENDERER_H
#define COLLECTABLE_RENDERER_H

#include <unordered_map>

#include "client/Framework.h"
#include "client/tweening/TransformTween.h"
#include "data/snapshot.h"
#include "multimedia/2d/Object2D.h"

#include "SpriteRendererData.h"

using std::unordered_map;

class CollectableRenderer: public Object2D {
private:
public:
    CollectableRenderer(CollectableData data, Vector2D position);

    ~CollectableRenderer();
};

#endif
