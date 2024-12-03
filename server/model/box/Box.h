#ifndef BOX_H
#define BOX_H
#include <cstdint>
#include <ctime>
#include <memory>
#include <optional>
#include <random>
#include <vector>

#include "data/snapshot.h"
#include "server/model/collectable/Collectable.h"
#include "server/model/collectable/CollectablesFactory.h"

class ProjectilesController;
class Config;
class Box {
private:
    Transform mySpace;
    uint8_t life;
    bool isDead;

public:
    Box() = default;
    explicit Box(const Vector2D& pos);
    std::optional<std::shared_ptr<Collectable>> GetContent(CollectablesFactory& factory);
    const Transform& GetTransform() const { return mySpace; }
    void ReceiveDamage(uint8_t damage);
    bool IsDead() const { return isDead; }
};

#endif
