#ifndef BULLET_RENDERER_H
#define BULLET_RENDERER_H

#include <unordered_map>

#include "common/Transform.h"

#include "Camera.h"
#include "Object2D.h"
#include "SpriteRendererData.h"

using std::unordered_map;

class BulletRenderer: public Object2D {
private:
    const unordered_map<TypeProjectile, SpriteRendererData> bulletsDataMap = {
            {TypeProjectile::BULLET, SpriteRendererData("machine_guns.png", "machine_guns.yaml",
                                                        "machine_bullet", Vector2D(1, 1))},
            {TypeProjectile::LASER,
             SpriteRendererData("laser.png", "laser.yaml", "laser_ray", Vector2D(3, 1.5))},
            {TypeProjectile::GRANADA_FRAGMENT, SpriteRendererData("", "", "")},
            {TypeProjectile::BANANA, SpriteRendererData("", "", "")}};

    Vector2D origin;
    Vector2D end;
    float speed;
    bool alive;

    SpriteRendererData renderData;

public:
    BulletRenderer(TypeProjectile type, Vector2D origin, Vector2D end, float speed = 105):
            origin(origin), end(end), speed(speed), alive(true) {
        renderData = bulletsDataMap.at(type);
        SetFileName(renderData.imageFile);
        SetSourceRect(renderData.GetSourceRect());
        SetTransform(Transform(origin, renderData.size, renderData.angle));
        GetTransform().LookAt(end, Vector2D::Right(), renderData.angle);
    }

    void Update(float deltaTime) {
        Vector2D dir = (end - origin).Normalized();
        GetTransform().Move(dir * speed * deltaTime);
        if (Vector2D::Distance(GetTransform().GetPos(), origin) >= (end - origin).GetMagnitude()) {
            alive = false;
            SetVisible(false);
        }
    }

    bool IsAlive() { return alive; }

    ~BulletRenderer() = default;
};

#endif
