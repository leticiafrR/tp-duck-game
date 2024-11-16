#ifndef BULLET_RENDERER_H
#define BULLET_RENDERER_H

#include "common/Transform.h"

#include "Camera.h"
#include "Object2D.h"
#include "SheetDataCache.h"

class BulletRenderer {
private:
    Object2D spr;
    Vector2D origin;
    Vector2D end;
    float speed;
    bool alive;

public:
    BulletRenderer(Vector2D origin, Vector2D end, float speed = 10, Vector2D size = Vector2D(1, 1)):
            spr("machine_guns.png", Transform(origin, size)),
            origin(origin),
            end(end),
            speed(speed),
            alive(true) {
        spr.GetTransform().LookAt(end);
        spr.SetSourceRect(SheetDataCache::GetData("machine_guns.yaml")["machine_bullet"][0]);
    }

    void Update(float deltaTime) {
        Vector2D dir = (end - origin).Normalized();
        spr.GetTransform().Move(dir * speed * deltaTime);
        if (Vector2D::Distance(spr.GetTransform().GetPos(), origin) >=
            (end - origin).GetMagnitude()) {
            alive = false;
        }
    }

    void Draw(Camera& cam) {
        if (!alive)
            return;
        spr.Draw(cam);
    }

    bool IsAlive() { return alive; }

    ~BulletRenderer() = default;
};

#endif
