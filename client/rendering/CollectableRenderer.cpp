#include "CollectableRenderer.h"

CollectableRenderer::CollectableRenderer(CollectableData data, Vector2D position) {
    SetFileName(data.file);
    SetSourceRect(data.rect);

    SetTransform(Transform(position, data.size, data.angle));
}

CollectableRenderer::~CollectableRenderer() = default;
