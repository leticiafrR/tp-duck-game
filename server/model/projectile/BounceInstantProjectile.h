
#ifndef BOUNCE_INSTANT_PROJECTILE_H
#define BOUNCE_INSTANT_PROJECTILE_H
#include <cmath>
#include <optional>
#include <unordered_map>
#include <utility>

#include "InstantProjectile.h"

class BounceInstantProjectile: public InstantProjectile {
private:
    std::optional<std::pair<float, Duck*>> CheckImpactWithSomeDuck(
            const std::unordered_map<PlayerID_t, Duck*>& players);
    void HandleCollisionWithMap(std::pair<float, bool> infoCollision);
    void HandleCollisionWithDuck(std::pair<float, Duck*> infoCollision);
    bool CheckCollision(const StaticMap& map, const std::unordered_map<PlayerID_t, Duck*>& players);

public:
    BounceInstantProjectile(const Vector2D& origin, const Vector2D& direction, float scope,
                            uint8_t damage, TypeProjectile type, InstantProjectileEventListener* l);


    void Update(const StaticMap& map, std::unordered_map<PlayerID_t, Duck*>& players) override;
};


#endif
