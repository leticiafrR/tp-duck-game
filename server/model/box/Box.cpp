#include "Box.h"

#include "server/model/collectable/spawning/includesCollectables.h"


Box::Box(const Vector2D& pos): mySpace(pos, Vector2D(2, 2)), life(30), isDead(false) {}

TypeItem Box::GetRandomTypeContent() {
    std::srand(std::time(nullptr));
    int randomIndex = std::rand() % (static_cast<int>(TypeItem::__collectableCount) +
                                     2);  //+2 incluye caso de explosiòn y caso de nada
    return static_cast<TypeItem>(randomIndex);
}

std::shared_ptr<Collectable> Box::GetSelectionCollectable(
        TypeItem type, ProjectilesController& projectilesController, const Config& conf) {
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


std::optional<std::shared_ptr<Collectable>> Box::GetContent(ProjectilesController& projectiles,
                                                            const Config& conf) {
    TypeItem type = GetRandomTypeContent();
    if (type < TypeItem::__collectableCount) {
        return GetSelectionCollectable(type, projectiles, conf);
    } else if (type == TypeItem::__collectableCount) {
        return std::shared_ptr<Collectable>(nullptr);
    }
    return std::nullopt;
}


void Box::ReceiveDamage(uint8_t damage) {
    if (life <= damage) {
        isDead = true;
    } else {
        life -= damage;
    }
}
