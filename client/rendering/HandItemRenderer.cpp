#include "HandItemRenderer.h"

HendItemRenderData::HendItemRenderData() {}

HendItemRenderData::HendItemRenderData(const string& imageFile, const string& yamlFile,
                                       const string& rectId, Vector2D offset, Vector2D size,
                                       float angle):
        SpriteRendererData(imageFile, yamlFile, rectId, size, angle) {
    this->offset = offset;
}

HendItemRenderData::~HendItemRenderData() = default;

Transform HendItemRenderData::GetTargetTransform(Vector2D playerPos) {
    return Transform(playerPos + offset, size, angle);
}


HandItemRenderer::HandItemRenderer(Transform& playerT, TypeCollectable type): playerT(playerT) {
    SetItem(type);
}

HandItemRenderer::~HandItemRenderer() = default;

void HandItemRenderer::SetItem(TypeCollectable type) {
    if (!itemsMap.contains(type)) {
        std::cout << "item not recognized\n";
        return;
    }
    itemData = itemsMap.at(type);
    SetFileName(itemData.imageFile);
    SetSourceRect(itemData.GetSourceRect());

    SetTransform(Transform(playerT.GetPos() + itemData.offset, itemData.size, itemData.angle));
}

void HandItemRenderer::Update(bool playerFlip, bool lookingUp) {
    SetFlip(playerFlip);
    GetTransform().SetPos(playerT.GetPos() + itemData.offset +
                          (lookingUp ? Vector2D(0, 0.6f) : Vector2D::Zero()));

    if (lookingUp) {
        GetTransform().SetAngle((playerFlip ? -90 - itemData.angle : 90 + itemData.angle));
    } else {
        GetTransform().SetAngle(playerFlip ? -itemData.angle : itemData.angle);
    }
}
