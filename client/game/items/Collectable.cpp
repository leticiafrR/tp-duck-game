#include "Collectable.h"

Collectable::Collectable(CollectableData data, Vector2D position) {
    SetFileName(data.file);
    SetSourceRect(data.rect);

    SetTransform(Transform(position, data.size, data.angle));
}

Collectable::~Collectable() = default;
