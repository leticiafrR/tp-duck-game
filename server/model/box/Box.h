#ifndef BOX_H
#define BOX_H


#include <memory>
#include <optional>

#include <stdint.h>

#include "common/Transform.h"

class CollectablesFactory;
class Collectable;


class Box {
private:
    Transform mySpace;
    uint8_t life;
    bool isDead;

public:
    Box() = default;
    explicit Box(const Vector2D& pos);
    std::optional<std::shared_ptr<Collectable>> GetContent(CollectablesFactory& factory);
    const Transform& GetTransform() const;
    void ReceiveDamage(uint8_t damage);
    bool IsDead() const;
};

#endif
