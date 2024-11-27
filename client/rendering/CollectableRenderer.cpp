#include "CollectableRenderer.h"

CollectableRenderer::CollectableRenderer(TypeCollectable type, Vector2D position):
        sizeTween(transform) {
    SetItem(type, position);
}
CollectableRenderer::~CollectableRenderer() = default;

void CollectableRenderer::SetItem(TypeCollectable type, Vector2D position) {
    if (!itemsMap.contains(type)) {
        std::cout << "collectable item not recognized\n";
        return;
    }
    SpriteRendererData itemData = itemsMap.at(type);
    SetFileName(itemData.imageFile);
    SetSourceRect(itemData.GetSourceRect());

    SetTransform(Transform(position, itemData.size, itemData.angle));

    sizeTween.SetTarget(transform.GetSize() * 1.2f, 0.6f);
    sizeTween.SetLoops(-1, LoopType::Yoyo);
}
