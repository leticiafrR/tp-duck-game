#include "Collectable.h"

#include "server/model/Duck.h"
Collectable::Collectable(const Transform& initialSpace): mySpace(initialSpace) {}
bool Collectable::Use(Duck* user) {
    user->TryEquip();
    return true;
}
Transform& Collectable::GetTransform() { return mySpace; }
bool Collectable::StillReusable() { return true; }

void Collectable::BeDropped(const Vector2D& duckPosition) { mySpace.SetPos(duckPosition); }
