#ifndef HAND_ITEM_RENDERER_H
#define HAND_ITEM_RENDERER_H
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "common/Transform.h"
#include "data/snapshot.h"

#include "Object2D.h"
#include "SheetDataCache.h"

using std::string;
using std::unordered_map;

class HendItemRenderData {
private:
public:
    string imageFile;
    string yamlFile;
    string rectId;
    Transform offsetT;

    HendItemRenderData() {}

    HendItemRenderData(const string& imageFile, const string& yamlFile, const string& rectId,
                       Transform offsetT = Transform()) {
        this->imageFile = imageFile;
        this->yamlFile = yamlFile;
        this->rectId = rectId;
        this->offsetT = offsetT;
    }

    Transform GetTargetTransform(Vector2D playerPos) {
        Transform target = offsetT;
        target.SetPos(playerPos + offsetT.GetPos());
        return target;
    }

    Vector2D GetOffset() { return offsetT.GetPos(); }
    float GetAngle() { return offsetT.GetAngle(); }

    SDL2pp::Optional<Rect> GetSourceRect() const {
        if (yamlFile.empty())
            return SDL2pp::NullOpt;
        return SheetDataCache::GetData(yamlFile)[rectId][0];
    }

    ~HendItemRenderData() = default;
};


class HandItemRenderer: public Object2D {
private:
    const unordered_map<TypeCollectable, HendItemRenderData> itemsMap = {
            {TypeCollectable::EMPTY, HendItemRenderData("", "", "")},
            {TypeCollectable::COWBOY_PISTOL,
             HendItemRenderData("pistols.png", "pistols.yaml", "cowboy_pistol",
                                Transform(Vector2D(0, -0.4f), Vector2D(2.8, 1.4)))},
            {TypeCollectable::LASER_RIFLE,
             HendItemRenderData("laser.png", "laser.yaml", "laser_rifle",
                                Transform(Vector2D(0, -0.5f), Vector2D(4, 4), -40))},
            {TypeCollectable::ARMOR, HendItemRenderData("", "", "")},
            {TypeCollectable::HELMET, HendItemRenderData("", "", "")}};

    Transform& playerT;
    HendItemRenderData itemData;

public:
    HandItemRenderer(Transform& playerT, TypeCollectable type): playerT(playerT) { SetItem(type); }

    void SetItem(TypeCollectable type) {
        itemData = itemsMap.at(type);
        SetFileName(itemData.imageFile);
        SetColor(ColorExtension::White());
        SetSourceRect(itemData.GetSourceRect());
        SetTransform(itemData.offsetT);

        GetTransform().SetPos(playerT.GetPos() + itemData.GetOffset());
    }

    void Update(bool playerFlip, bool lookingUp) {
        SetFlip(playerFlip);
        GetTransform().SetPos(playerT.GetPos() + itemData.GetOffset() +
                              (lookingUp ? Vector2D(0, 0.6f) : Vector2D::Zero()));

        if (lookingUp) {
            GetTransform().SetAngle((playerFlip ? -90 : 90));
        } else {
            GetTransform().SetAngle(playerFlip ? -itemData.GetAngle() : itemData.GetAngle());
        }
    }
    ~HandItemRenderer() = default;
};

#endif
