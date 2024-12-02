#ifndef RESOURCE_CONSTANTS_H
#define RESOURCE_CONSTANTS_H

#include <string>
#include <unordered_map>

#include "data/snapshot.h"
#include "multimedia/ColorExtension.h"

using std::string;
using std::unordered_map;

const string RESOURCE_ROOT = "resources.yaml";

const unordered_map<string, TypeProjectile> PROJECTILES{{"machine_bullet", TypeProjectile::BULLET},
                                                        {"laser_ray", TypeProjectile::LASER},
                                                        {"fragment", TypeProjectile::FRAGMENT},
                                                        {"banana", TypeProjectile::BANANA}};

const unordered_map<string, TypeCollectable> COLLECTABLES{
        {"empty", TypeCollectable::EMPTY},
        {"ak_47", TypeCollectable::AK47},
        {"banana", TypeCollectable::BANANA},
        {"banana_peel", TypeCollectable::BANANA_PEEL},
        {"grenade", TypeCollectable::GRENADE},
        {"grenade_unlock", TypeCollectable::GRENADE_UNLOCK},
        {"cowboy_pistol", TypeCollectable::COWBOY_PISTOL},
        {"dueling_pistol", TypeCollectable::DUELING_PISTOL},
        {"armor", TypeCollectable::ARMOR},
        {"helmet", TypeCollectable::HELMET},
        {"laser_rifle", TypeCollectable::LASER_RIFLE},
        {"magnum", TypeCollectable::MAGNUM},
        {"pew_pew_laser", TypeCollectable::PEW_PEW_LASER},
        {"shotgun", TypeCollectable::SHOTGUN},
        {"sniper", TypeCollectable::SNIPER}};

const unordered_map<uint8_t, Color> DUCK_SKIN_COLORS = {
        {0, ColorExtension::White()}, {1, ColorExtension::Yellow()},
        {2, ColorExtension::Blue()},  {3, ColorExtension::Orange()},
        {4, ColorExtension::Cyan()},  {5, ColorExtension::Purple()}};

#endif
