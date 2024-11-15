#ifndef PROJECTILE_H
#define PROJECTILE_H


#include <unordered_map>

#include "data/id.h"
#include "data/snapshot.h"

class StaticMap;
class Duck;

class Projectile {
protected:
    TypeProjectile type;
    bool isDead;

public:
    void MarkAsDead() { isDead = true; }
    bool IsDead() { return isDead; }
    explicit Projectile(TypeProjectile type): type(type), isDead(false) {}
    virtual ~Projectile() = default;
    virtual void Update(const StaticMap& map, std::unordered_map<PlayerID_t, Duck*>& players) = 0;
};

// class PhysicalProjectile: public Projectile{
//     //no me voy a preocupar por esto aun
// };

#endif
