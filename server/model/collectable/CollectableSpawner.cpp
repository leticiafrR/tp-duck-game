#include "CollectableSpawner.h"

#include "Collectables.h"
#define COLLECTABLE_SIZE 2
CollectableSpawner::CollectableSpawner(const Vector2D& pos,
                                       ProjectilesController& projectilesController,
                                       const Config& conf):
        timeToRespawn(3),
        timer(std::make_shared<float>(0)),
        spawnPlace(pos, Vector2D(COLLECTABLE_SIZE, COLLECTABLE_SIZE)),
        projectilesController(projectilesController),
        conf(conf) {}


TypeCollectable CollectableSpawner::GetRandomTypeCollectable() {
    std::srand(std::time(nullptr));
    int randomIndex = std::rand() % static_cast<int>(TypeCollectable::__typesCount);
    return static_cast<TypeCollectable>(randomIndex);
}

Collectable* CollectableSpawner::GetCollectable(TypeCollectable type) {
    switch (type) {
        case TypeCollectable::DUELING_PISTOL:
            return new DuelingPistol(projectilesController, spawnPlace, conf);
            break;
        case TypeCollectable::LASER_RIFLE:
            return new LaserRifle(projectilesController, spawnPlace, conf);
            break;
        case TypeCollectable::PEW_PEW_LASER:
            return new PewPewLaser(projectilesController, spawnPlace, conf);
            break;
        case TypeCollectable::COWBOY_PISTOL:
            return new PistolaCowboy(projectilesController, spawnPlace, conf);
            break;
        case TypeCollectable::SHOTGUN:
            return new Shotgun(projectilesController, spawnPlace, conf);
            break;
        // case TypeCollectable::ARMOR:
        //     return new a(projectilesController, spawnPlace,conf);
        //     break;
        default:
            break;
    }
    std::cout << "selecciòn aun no implementada :(. Mientras tanto una pew pew\n";
    return new PewPewLaser(projectilesController, spawnPlace, conf);
}

void CollectableSpawner::Update(float deltaTime, Collectables& collectables) {
    if ((*timer) < timeToRespawn && (*timer) + deltaTime >= timeToRespawn) {
        Collectable* obj = GetCollectable(GetRandomTypeCollectable());
        collectables.SpawnCollectable(obj, timer);
    }
    (*timer) += deltaTime;
}
