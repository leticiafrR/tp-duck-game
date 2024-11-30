#ifndef THROWABLE_RENDERER_H
#define THROWABLE_RENDERER_H

#include <unordered_map>

#include "client/Framework.h"

#include "SpriteRendererData.h"

using std::unordered_map;

class ThrowableRenderer: public Object2D {
private:
    const unordered_map<TypeCollectable, SpriteRendererData> itemsMap = {
            {TypeCollectable::BANANA,
             SpriteRendererData("grenades.png", "grenades.yaml", "banana", Vector2D(2, 2))},
            {TypeCollectable::GRENADE,
             SpriteRendererData("grenades.png", "grenades.yaml", "grenade", Vector2D(2, 2))}};

    Vector2D fromPos;
    Vector2D targetPos;
    float tLerp;

public:
    ThrowableRenderer(TypeCollectable type, Vector2D target);

    void SetTargetPos(Vector2D target);

    void Update(float deltaTime);

    ~ThrowableRenderer();
};

#endif
