#ifndef HAND_ITEM_RENDERER_H
#define HAND_ITEM_RENDERER_H
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "common/Transform.h"
#include "data/snapshot.h"
#include "multimedia/Object2D.h"
#include "multimedia/SheetDataCache.h"

#include "SpriteRendererData.h"

using std::string;
using std::unordered_map;

class HendItemRenderData: public SpriteRendererData {
private:
public:
    Vector2D offset;

    HendItemRenderData() {}

    HendItemRenderData(const string& imageFile, const string& yamlFile, const string& rectId,
                       Vector2D offset = Vector2D::Zero(), Vector2D size = Vector2D::Zero(),
                       float angle = 0):
            SpriteRendererData(imageFile, yamlFile, rectId, size, angle) {
        this->offset = offset;
    }

    Transform GetTargetTransform(Vector2D playerPos) {
        return Transform(playerPos + offset, size, angle);
    }

    ~HendItemRenderData() = default;
};


class HandItemRenderer: public Object2D {
private:
    const unordered_map<TypeCollectable, HendItemRenderData> itemsMap = {
            {TypeCollectable::EMPTY, HendItemRenderData("", "", "")},
            {TypeCollectable::COWBOY_PISTOL,
             HendItemRenderData("pistols.png", "pistols.yaml", "cowboy_pistol", Vector2D(0, -0.4f),
                                Vector2D(2.8, 1.4))},
            {TypeCollectable::DUELING_PISTOL,
             HendItemRenderData("pistols.png", "pistols.yaml", "dueling_pistol", Vector2D(0, -0.4f),
                                Vector2D(4, 4))},
            {TypeCollectable::AK47,
             HendItemRenderData("machine_guns.png", "machine_guns.yaml", "ak_47",
                                Vector2D(0, -0.4f), Vector2D(4, 4))},
            {TypeCollectable::PEW_PEW_LASER,
             HendItemRenderData("laser.png", "laser.yaml", "pew_pew_laser", Vector2D(0, -0.4f),
                                Vector2D(4, 4))},
            {TypeCollectable::LASER_RIFLE,
             HendItemRenderData("laser.png", "laser.yaml", "laser_rifle", Vector2D(0, -0.5f),
                                Vector2D(4, 4), -45)},
            {TypeCollectable::SHOTGUN,
             HendItemRenderData("shotguns.png", "shotguns.yaml", "shotgun", Vector2D(0, -0.4f),
                                Vector2D(4, 4))},
            {TypeCollectable::ARMOR, HendItemRenderData("", "", "")},
            {TypeCollectable::HELMET, HendItemRenderData("", "", "")}};

    Transform& playerT;
    HendItemRenderData itemData;

public:
    HandItemRenderer(Transform& playerT, TypeCollectable type): playerT(playerT) { SetItem(type); }

    void SetItem(TypeCollectable type) {
        if (!itemsMap.contains(type)) {
            std::cout << "item not recognized\n";
            return;
        }
        itemData = itemsMap.at(type);
        SetFileName(itemData.imageFile);
        SetSourceRect(itemData.GetSourceRect());

        SetTransform(Transform(playerT.GetPos() + itemData.offset, itemData.size, itemData.angle));
    }

    void Update(bool playerFlip, bool lookingUp) {
        SetFlip(playerFlip);
        GetTransform().SetPos(playerT.GetPos() + itemData.offset +
                              (lookingUp ? Vector2D(0, 0.6f) : Vector2D::Zero()));

        if (lookingUp) {
            GetTransform().SetAngle((playerFlip ? -90 - itemData.angle : 90 + itemData.angle));
        } else {
            GetTransform().SetAngle(playerFlip ? -itemData.angle : itemData.angle);
        }
    }
    ~HandItemRenderer() = default;
};

#endif
