#include "HandItemRenderer.h"

HandItemRenderer::HandItemRenderer(Transform& playerT, CollectableData data): playerT(playerT) {
    SetItem(data);
}

HandItemRenderer::~HandItemRenderer() = default;

void HandItemRenderer::SetItem(CollectableData data) {
    SetFileName(data.file);
    SetSourceRect(data.rect);

    angle = data.angle;

    SetTransform(Transform(playerT.GetPos() + offset, data.size, angle));
}

void HandItemRenderer::Update(bool playerFlip, bool lookingUp) {
    SetFlip(playerFlip);
    transform.SetPos(playerT.GetPos() + offset +
                     (lookingUp ? Vector2D(0, 0.6f) : Vector2D::Zero()));

    if (lookingUp) {
        transform.SetAngle((playerFlip ? -90 - angle : 90 + angle));
    } else {
        transform.SetAngle(playerFlip ? -angle : angle);
    }
}
