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

const unordered_map<string, TypeItem> COLLECTABLES{{"empty", TypeItem::EMPTY},
                                                   {"ak_47", TypeItem::AK47},
                                                   {"banana", TypeItem::BANANA},
                                                   {"banana_peel", TypeItem::BANANA_PEEL},
                                                   {"grenade", TypeItem::GRENADE},
                                                   {"grenade_unlock", TypeItem::GRENADE_UNLOCK},
                                                   {"cowboy_pistol", TypeItem::COWBOY_PISTOL},
                                                   {"dueling_pistol", TypeItem::DUELING_PISTOL},
                                                   {"armor", TypeItem::ARMOR},
                                                   {"helmet", TypeItem::HELMET},
                                                   {"laser_rifle", TypeItem::LASER_RIFLE},
                                                   {"magnum", TypeItem::MAGNUM},
                                                   {"pew_pew_laser", TypeItem::PEW_PEW_LASER},
                                                   {"shotgun", TypeItem::SHOTGUN},
                                                   {"sniper", TypeItem::SNIPER}};

const unordered_map<uint8_t, Color> DUCK_SKIN_COLORS = {
        {0, ColorExtension::White()}, {1, ColorExtension::Yellow()},
        {2, ColorExtension::Blue()},  {3, ColorExtension::Orange()},
        {4, ColorExtension::Cyan()},  {5, ColorExtension::Purple()}};

#endif
