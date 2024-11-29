#include "Collectable.h"

#include "server/model/Duck.h"
Collectable::Collectable(const Transform& initialSpace): mySpace(initialSpace) {}
bool Collectable::Use(Duck* user) {
    user->TryEquip();
    return true;
}
const Transform& Collectable::GetTransform() const { return mySpace; }
bool Collectable::StillReusable() { return true; }

void Collectable::BeDropped(const Vector2D& duckPosition) { mySpace.SetPos(duckPosition); }
