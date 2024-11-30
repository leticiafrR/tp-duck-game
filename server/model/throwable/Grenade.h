#ifndef GRENADE_H
#define GRENADE_H
#include "server/model/projectile/ProjectilesController.h"

#include "Throwable.h"

class Grenade: public Throwable {
private:
    ProjectilesController& projectiles;
    float timer;
    void Explote();

public:
    explicit Grenade(ProjectilesController& projectilesController);
    void Update(const StaticMap& map, float deltaTime) override;
    ~Grenade() = default;
    TypeCollectable GetTypeCollectable() override;
};


#endif
