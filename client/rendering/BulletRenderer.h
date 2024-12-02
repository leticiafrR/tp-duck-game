#ifndef BULLET_RENDERER_H
#define BULLET_RENDERER_H

#include <unordered_map>

#include "client/Framework.h"
#include "common/Transform.h"
#include "data/snapshot.h"
#include "multimedia/2d/Object2D.h"
#include "multimedia/Camera.h"

#include "SpriteRendererData.h"

using std::unordered_map;

class BulletRenderer: public Object2D {
private:
    Vector2D origin;
    Vector2D end;
    float speed;
    bool alive;

    SpriteRendererData renderData;

public:
    BulletRenderer(ProjectileData data, Vector2D origin, Vector2D end);
    ~BulletRenderer();

    void Update(float deltaTime);
    bool IsAlive();
};

#endif
