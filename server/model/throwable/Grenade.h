#ifndef GRENADE_H
#define GRENADE_H
#include <unordered_map>

#include "server/model/projectile/ProjectilesController.h"

#include "Throwable.h"

class Grenade: public Throwable {
private:
    ProjectilesController& projectiles;
    float timer;
    void Explote();

public:
    explicit Grenade(ProjectilesController& projectilesController, TypeItem type);
    ~Grenade() = default;
    void Update(const StaticMap& map, float deltaTime) override;
    void CheckCollisionWithDucks(std::unordered_map<PlayerID_t, Duck*>& /*ducks*/) override;
};


#endif
