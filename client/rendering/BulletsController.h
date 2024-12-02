#ifndef BULLETS_CONTROLLER_H
#define BULLETS_CONTROLLER_H

#include <list>

#include "client/Framework.h"

#include "BulletRenderer.h"

using std::list;

class BulletsController {
private:
    ResourceManager& resourceManager;
    AudioManager& audioManager;
    list<BulletRenderer> bullets;

public:
    BulletsController(ResourceManager& resourceManager, AudioManager& audioManager);
    ~BulletsController();

    void SpawnBullet(ProjectileEventDto projectilData);
    void ReapDead();

    void Draw(float deltaTime, Camera& cam);
};

#endif
