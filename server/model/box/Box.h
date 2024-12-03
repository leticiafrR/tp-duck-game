#ifndef BOX_H
#define BOX_H


#include <memory>
#include <optional>

#include "common/Transform.h"

class CollectablesFactory;
class Collectable;

class Box {
private:
    Transform mySpace;
    int life;
    bool isDead;

public:
    Box(const Transform& initialSpace, int life);
    std::optional<std::shared_ptr<Collectable>> GetContent(CollectablesFactory& factory);
    const Transform& GetTransform() const;
    void ReceiveDamage(uint8_t damage);
    bool IsDead() const;
    Box() = default;
};

#endif
