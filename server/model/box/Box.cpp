#include "Box.h"

#include "server/model/collectable/CollectablesFactory.h"
#define LIFE_BOX 25
Box::Box(const Vector2D& position):
        mySpace(position, Vector2D(2, 2)), life(LIFE_BOX), isDead(false) {}

std::optional<std::shared_ptr<Collectable>> Box::GetContent(CollectablesFactory& factory) {
    return factory.MaybeRandomCollectable(mySpace.GetPos());
}

void Box::ReceiveDamage(uint8_t damage) {
    if (life <= damage) {
        isDead = true;
    } else {
        life -= damage;
    }
}

bool Box::IsDead() const { return isDead; }
const Transform& Box::GetTransform() const { return mySpace; }
