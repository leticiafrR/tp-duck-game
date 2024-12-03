#include "CollectablesFactory.h"

#include <cstdint>
#include <ctime>
#include <memory>
#include <optional>
#include <random>
#include <vector>

#include "data/snapshot.h"
#include "server/model/collectable/Collectable.h"
#include "server/model/collectable/spawning/includesCollectables.h"

#define SIZE_COLLECTABLE 2

CollectablesFactory::CollectablesFactory(ProjectilesController& projectilesController,
                                         const Config& conf):
        projectilesController(projectilesController), conf(conf) {}

std::optional<std::shared_ptr<Collectable>> CollectablesFactory::MaybeRandomCollectable(
        const Vector2D& position) {
    TypeItem type = GetRandomTypeCollectable(2);
    if (type < TypeItem::__collectableCount) {
        return CreateCollectable(type, position);
    } else if (type == TypeItem::__collectableCount) {
        return std::shared_ptr<Collectable>(nullptr);
    }
    return std::nullopt;
}


TypeItem CollectablesFactory::GetRandomTypeCollectable(int cantAditionalOptions) {
    std::srand(std::time(nullptr));
    int randomIndex =
            std::rand() % (static_cast<int>(TypeItem::__collectableCount) + cantAditionalOptions);
    return static_cast<TypeItem>(randomIndex);
}

std::shared_ptr<Collectable> CollectablesFactory::CreateRandomCollectable(
        const Vector2D& position) {
    TypeItem type = GetRandomTypeCollectable();
    return CreateCollectable(type, position);
}

std::shared_ptr<Collectable> CollectablesFactory::CreateCollectable(TypeItem type,
                                                                    const Vector2D& position) {
    Transform mySpace(position, Vector2D(SIZE_COLLECTABLE, SIZE_COLLECTABLE));
    switch (type) {
        case TypeItem::DUELING_PISTOL:
            std::cout << "[BOX]: DUELING_PISTOL\n";
            return std::make_shared<DuelingPistol>(projectilesController, mySpace, conf);
            break;
        case TypeItem::LASER_RIFLE:
            std::cout << "[BOX]: LASER_RIFLE\n";
            return std::make_shared<LaserRifle>(projectilesController, mySpace, conf);
            break;
        case TypeItem::PEW_PEW_LASER:
            std::cout << "[BOX]: PEW_PEW_LASER\n";
            return std::make_shared<PewPewLaser>(projectilesController, mySpace, conf);
            break;
        case TypeItem::COWBOY_PISTOL:
            std::cout << "[BOX]: COWBOY\n";
            return std::make_shared<PistolaCowboy>(projectilesController, mySpace, conf);
            break;
        case TypeItem::SHOTGUN:
            std::cout << "[BOX]: SHOTGUN\n";
            return std::make_shared<Shotgun>(projectilesController, mySpace, conf);
            break;
        case TypeItem::ARMOR:
            std::cout << "[BOX]: ARMORY\n";
            return std::make_shared<Armor>(mySpace);
            break;
        case TypeItem::HELMET:
            std::cout << "[BOX]: HELMET\n";
            return std::make_shared<Helmet>(mySpace);
            break;
        case TypeItem::GRENADE:
            std::cout << "[BOX]: GRENADE\n";
            return std::make_shared<GrenadeCollectable>(projectilesController, mySpace);
            break;
        case TypeItem::AK47:
            std::cout << "[BOX]: AK47\n";
            return std::make_shared<AK47>(projectilesController, mySpace, conf);
            break;
        case TypeItem::MAGNUM:
            std::cout << "[BOX]: MAGNUM\n";
            return std::make_shared<Magnum>(projectilesController, mySpace, conf);
            break;
        case TypeItem::BANANA:
            std::cout << "[BOX]: BANAN\n";
            return std::make_shared<BananaCollectable>(mySpace);
            break;
        default:
            break;
    }
    return std::make_shared<GrenadeCollectable>(projectilesController, mySpace);
}
