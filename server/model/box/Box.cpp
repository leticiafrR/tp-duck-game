#include "Box.h"

#include "server/model/collectable/CollectablesFactory.h"

Box::Box(const Transform& initialSpace, int life):
        mySpace(initialSpace), life(life), isDead(false) {}

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
