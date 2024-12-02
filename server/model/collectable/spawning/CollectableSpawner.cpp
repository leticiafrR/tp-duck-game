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


TypeItem CollectableSpawner::GetRandomTypeCollectable() {
    std::srand(std::time(nullptr));
    int randomIndex = std::rand() % static_cast<int>(TypeItem::__collectableCount);
    return static_cast<TypeItem>(randomIndex);
}

std::shared_ptr<Collectable> CollectableSpawner::GetCollectable(TypeItem type) {
    switch (type) {
        case TypeItem::DUELING_PISTOL:
            return std::make_shared<DuelingPistol>(projectilesController, spawnPlace, conf);
            break;
        case TypeItem::LASER_RIFLE:
            return std::make_shared<LaserRifle>(projectilesController, spawnPlace, conf);
            break;
        case TypeItem::PEW_PEW_LASER:
            return std::make_shared<PewPewLaser>(projectilesController, spawnPlace, conf);
            break;
        case TypeItem::COWBOY_PISTOL:
            return std::make_shared<PistolaCowboy>(projectilesController, spawnPlace, conf);
            break;
        case TypeItem::SHOTGUN:
            return std::make_shared<Shotgun>(projectilesController, spawnPlace, conf);
            break;
        case TypeItem::ARMOR:
            return std::make_shared<Armor>(spawnPlace);
            break;
        case TypeItem::HELMET:
            return std::make_shared<Helmet>(spawnPlace);
            break;
        case TypeItem::GRENADE:
            return std::make_shared<GrenadeCollectable>(projectilesController, spawnPlace);
            break;
        case TypeItem::AK47:
            return std::make_shared<AK47>(projectilesController, spawnPlace, conf);
            break;
        case TypeItem::MAGNUM:
            return std::make_shared<Magnum>(projectilesController, spawnPlace, conf);
            break;
        case TypeItem::BANANA:
            return std::make_shared<BananaCollectable>(spawnPlace);
            break;
        default:
            break;
    }
    return std::make_shared<BananaCollectable>(spawnPlace);
}

void CollectableSpawner::Update(float deltaTime, Collectables& collectables) {
    if ((*timer) < timeToRespawn && (*timer) + deltaTime >= timeToRespawn) {
        std::shared_ptr<Collectable> obj = GetCollectable(GetRandomTypeCollectable());
        collectables.SpawnCollectable(obj, timer);
    }
    (*timer) += deltaTime;
}
