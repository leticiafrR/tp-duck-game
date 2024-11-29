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

std::shared_ptr<Collectable> CollectableSpawner::GetCollectable(TypeCollectable type) {
    switch (type) {
        case TypeCollectable::DUELING_PISTOL:
            return std::make_shared<DuelingPistol>(projectilesController, spawnPlace, conf);
            break;
        case TypeCollectable::LASER_RIFLE:
            return std::make_shared<LaserRifle>(projectilesController, spawnPlace, conf);
            break;
        case TypeCollectable::PEW_PEW_LASER:
            return std::make_shared<PewPewLaser>(projectilesController, spawnPlace, conf);
            break;
        case TypeCollectable::COWBOY_PISTOL:
            return std::make_shared<PistolaCowboy>(projectilesController, spawnPlace, conf);
            break;
        case TypeCollectable::SHOTGUN:
            return std::make_shared<Shotgun>(projectilesController, spawnPlace, conf);
            break;
        case TypeCollectable::ARMOR:
            return std::make_shared<Armor>(spawnPlace);
            break;
        case TypeCollectable::HELMET:
            return std::make_shared<Helmet>(spawnPlace);
            break;
        default:
            break;
    }
    return std::make_shared<Helmet>(spawnPlace);
    // return std::make_shared<LaserRifle>(projectilesController, spawnPlace, conf);
    // return std::make_shared<Armor>(spawnPlace);
}

void CollectableSpawner::Update(float deltaTime, Collectables& collectables) {
    if ((*timer) < timeToRespawn && (*timer) + deltaTime >= timeToRespawn) {
        std::shared_ptr<Collectable> obj = GetCollectable(GetRandomTypeCollectable());
        collectables.SpawnCollectable(obj, timer);
    }
    (*timer) += deltaTime;
}
