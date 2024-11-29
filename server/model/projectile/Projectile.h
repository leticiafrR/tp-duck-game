#ifndef PROJECTILE_H
#define PROJECTILE_H


#include <unordered_map>

#include "data/id.h"
#include "data/snapshot.h"
class ReboundsController;
class StaticMap;
class Duck;

class Projectile {
protected:
    TypeProjectile type;
    bool isDead;

public:
    explicit Projectile(TypeProjectile type);
    virtual ~Projectile() = default;
    virtual void Update(const StaticMap& map, std::unordered_map<PlayerID_t, Duck*>& players) = 0;
    void MarkAsDead();
    bool IsDead();
};

#endif
