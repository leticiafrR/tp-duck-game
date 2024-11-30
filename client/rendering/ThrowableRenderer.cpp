#include "ThrowableRenderer.h"

ThrowableRenderer::ThrowableRenderer(TypeCollectable type, Vector2D target):
        fromPos(target), targetPos(target), tLerp(0) {

    if (!itemsMap.contains(type)) {
        std::cout << "item NOT recognized\n";
        return;
    }
    transform.SetPos(target);
    transform.SetSize(itemsMap.at(type).size);

    SetFileName(itemsMap.at(type).imageFile);
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
