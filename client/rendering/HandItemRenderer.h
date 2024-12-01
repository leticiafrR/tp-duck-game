#ifndef HAND_ITEM_RENDERER_H
#define HAND_ITEM_RENDERER_H
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "common/Transform.h"
#include "data/snapshot.h"
#include "multimedia/2d/Object2D.h"
#include "multimedia/cache/SheetDataCache.h"

#include "SpriteRendererData.h"

using std::string;
using std::unordered_map;

class HendItemRenderData: public SpriteRendererData {
private:
public:
    Vector2D offset;

    HendItemRenderData();

    HendItemRenderData(const string& imageFile, const string& yamlFile, const string& rectId,
                       Vector2D offset = Vector2D::Zero(), Vector2D size = Vector2D::Zero(),
                       float angle = 0);

    ~HendItemRenderData();

    Transform GetTargetTransform(Vector2D playerPos);
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

            {TypeCollectable::MAGNUM, HendItemRenderData("pistols.png", "pistols.yaml", "magnum",
                                                         Vector2D(0, -0.4f), Vector2D(4, 4))},

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

            {TypeCollectable::BANANA, HendItemRenderData("grenades.png", "grenades.yaml", "banana",
                                                         Vector2D(0, -0.4f), Vector2D(2, 2))},
            {TypeCollectable::GRENADE,
             HendItemRenderData("grenades.png", "grenades.yaml", "grenade", Vector2D(0, -0.4f),
                                Vector2D(2, 2))},


            {TypeCollectable::ARMOR, HendItemRenderData("defense.png", "defense.yaml", "chest",
                                                        Vector2D(0, -0.4f), Vector2D(2, 2))},
            {TypeCollectable::HELMET, HendItemRenderData("defense.png", "defense.yaml", "helmet",
                                                         Vector2D(0, -0.4f), Vector2D(2, 2))}};

    Transform& playerT;
    HendItemRenderData itemData;

public:
    HandItemRenderer(Transform& playerT, TypeCollectable type);
    ~HandItemRenderer();

    void SetItem(TypeCollectable type);

    void Update(bool playerFlip, bool lookingUp);
};

#endif
