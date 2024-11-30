#ifndef COLLECTABLE_RENDERER_H
#define COLLECTABLE_RENDERER_H

#include <unordered_map>

#include "client/tweening/TransformTween.h"
#include "data/snapshot.h"
#include "multimedia/2d/Object2D.h"

#include "SpriteRendererData.h"

using std::unordered_map;

class CollectableRenderer: public Object2D {
private:
    const unordered_map<TypeCollectable, SpriteRendererData> itemsMap = {
            {TypeCollectable::EMPTY, SpriteRendererData("", "", "")},
            {TypeCollectable::COWBOY_PISTOL,
             SpriteRendererData("pistols.png", "pistols.yaml", "cowboy_pistol",
                                Vector2D(2.8, 1.4))},
            {TypeCollectable::DUELING_PISTOL,
             SpriteRendererData("pistols.png", "pistols.yaml", "dueling_pistol", Vector2D(4, 4))},
            {TypeCollectable::AK47,
             SpriteRendererData("machine_guns.png", "machine_guns.yaml", "ak_47", Vector2D(4, 4))},
            {TypeCollectable::PEW_PEW_LASER,
             SpriteRendererData("laser.png", "laser.yaml", "pew_pew_laser", Vector2D(4, 4))},
            {TypeCollectable::LASER_RIFLE,
             SpriteRendererData("laser.png", "laser.yaml", "laser_rifle", Vector2D(4, 4), -45)},
            {TypeCollectable::SHOTGUN,
             SpriteRendererData("shotguns.png", "shotguns.yaml", "shotgun", Vector2D(4, 4))},

            {TypeCollectable::BANANA,
             SpriteRendererData("grenades.png", "grenades.yaml", "banana", Vector2D(2, 2))},
            {TypeCollectable::GRENADE,
             SpriteRendererData("grenades.png", "grenades.yaml", "grenade", Vector2D(2, 2))},

            {TypeCollectable::ARMOR,
             SpriteRendererData("defense.png", "defense.yaml", "chest", Vector2D(2, 2))},
            {TypeCollectable::HELMET,
             SpriteRendererData("defense.png", "defense.yaml", "helmet", Vector2D(2, 2))}};

    TransformTween sizeTween;

public:
    CollectableRenderer(TypeCollectable type, Vector2D position);

    void SetItem(TypeCollectable type, Vector2D position);

    ~CollectableRenderer();
};

#endif
