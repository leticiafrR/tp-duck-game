#ifndef BULLET_RENDERER_H
#define BULLET_RENDERER_H

#include <unordered_map>

#include "common/Transform.h"
#include "data/snapshot.h"
#include "multimedia/2d/Object2D.h"
#include "multimedia/Camera.h"

#include "SpriteRendererData.h"

using std::unordered_map;

class BulletRenderer: public Object2D {
private:
    const unordered_map<TypeProjectile, SpriteRendererData> bulletsDataMap = {
            {TypeProjectile::BULLET, SpriteRendererData("machine_guns.png", "machine_guns.yaml",
                                                        "machine_bullet", Vector2D(1, 1))},
            {TypeProjectile::LASER,
             SpriteRendererData("laser.png", "laser.yaml", "laser_ray", Vector2D(3, 1.5))},
            {TypeProjectile::FRAGMENT, SpriteRendererData("", "", "")},
            {TypeProjectile::BANANA, SpriteRendererData("", "", "")}};

    Vector2D origin;
    Vector2D end;
    float speed;
    bool alive;

    SpriteRendererData renderData;

public:
    BulletRenderer(TypeProjectile type, Vector2D origin, Vector2D end, float speed = 105);
    ~BulletRenderer();
    void Update(float deltaTime);

    bool IsAlive();
};

#endif
