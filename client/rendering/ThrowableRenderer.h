#ifndef THROWABLE_RENDERER_H
#define THROWABLE_RENDERER_H

#include <unordered_map>

#include "client/Framework.h"

#include "SpriteRendererData.h"

using std::unordered_map;

class ThrowableRenderer: public Object2D {
private:
    Vector2D fromPos;
    Vector2D targetPos;
    float tLerp;

public:
    ThrowableRenderer(CollectableData data, Vector2D target);

    void SetTargetPos(Vector2D target);

    void Update(float deltaTime);

    ~ThrowableRenderer();
};

#endif
