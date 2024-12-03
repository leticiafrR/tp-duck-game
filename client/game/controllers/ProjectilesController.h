#ifndef PROJECTILES_CONTROLLER_H
#define PROJECTILES_CONTROLLER_H

#include <list>

#include "../items/Projectile.h"
#include "client/Framework.h"

using std::list;

class BulletsController {
private:
    ResourceManager& resourceManager;
    AudioManager& audioManager;
    list<Projectile> bullets;

public:
    BulletsController(ResourceManager& resourceManager, AudioManager& audioManager);
    ~BulletsController();

    void SpawnBullet(ProjectileEventDto projectilData);
    void ReapDead();

    void Draw(float deltaTime, Camera& cam);
};

#endif
