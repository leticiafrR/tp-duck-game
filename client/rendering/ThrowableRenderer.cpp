#include "ThrowableRenderer.h"

ThrowableRenderer::ThrowableRenderer(TypeCollectable type, Vector2D target):
        Object2D(itemsMap.at(type).imageFile, Transform(target, itemsMap.at(type).size)),
        fromPos(target),
        targetPos(target),
        tLerp(0) {
    SetSourceRect(itemsMap.at(type).GetSourceRect());
}

void ThrowableRenderer::Update(float deltaTime) {
    tLerp += deltaTime * 13;

    Vector2D pos = Vector2D::Lerp(fromPos, targetPos, tLerp);
    transform.SetPos(pos);
}

void ThrowableRenderer::SetTargetPos(Vector2D target) {
    fromPos = transform.GetPos();
    tLerp = 0;
    targetPos = target;
}

ThrowableRenderer::~ThrowableRenderer() = default;
