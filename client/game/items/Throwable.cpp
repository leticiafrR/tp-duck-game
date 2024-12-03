#include "Throwable.h"

Throwable::Throwable(CollectableData data, Vector2D target):
        fromPos(target), targetPos(target), tLerp(0) {

    transform.SetPos(target);
    transform.SetSize(data.size);

    SetFileName(data.file);
    SetSourceRect(data.rect);
}

void Throwable::Update(float deltaTime) {
    tLerp += deltaTime * 13;

    Vector2D pos = Vector2D::Lerp(fromPos, targetPos, tLerp);
    transform.SetPos(pos);
}

void Throwable::SetTargetPos(Vector2D target) {
    fromPos = transform.GetPos();
    tLerp = 0;
    targetPos = target;
}

Throwable::~Throwable() = default;
