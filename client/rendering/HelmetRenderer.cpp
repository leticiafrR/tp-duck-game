#include "HelmetRenderer.h"

HelmetRenderer::HelmetRenderer(Transform& playerT, CollectableData data):
        follow(transform, playerT, Vector2D(0, 0.8f)) {
    SetFileName(data.file);
    SetSourceRect(data.rect);
    transform.SetSize(Vector2D(2.32f, 2.32f));
}

void HelmetRenderer::Update(bool flip, bool crouched) {
    transform.SetAngle(!crouched ? 0 : (flip ? -90 : 90));

    follow.SetOffset(!crouched ? Vector2D(0, 0.8f) : Vector2D(flip ? 1.0f : -1.0f, -1.0f));
    follow.Follow();

    SetFlip(flip);
}

HelmetRenderer::~HelmetRenderer() = default;
