#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <unordered_map>

#include "client/Framework.h"
#include "common/Transform.h"
#include "data/snapshot.h"

using std::unordered_map;

class Projectile: public Object2D {
private:
    Vector2D origin;
    Vector2D end;
    float speed;
    bool alive;

public:
    Projectile(ProjectileData data, Vector2D origin, Vector2D end);
    ~Projectile();

    void Update(float deltaTime);
    bool IsAlive();
};

#endif
