#ifndef CONSTANTSERVER_H
#define CONSTANTSERVER_H

#include <string>

/************************************STATIC MAP YAML*******************************/
const float HALF = 2;
const float FALLING = -1;

/****************************************DUCK CONFIG*******************************/
const std::string SPEED_STR = "speed";
const std::string MASS_STR = "mass";
const std::string SIZE_STR = "size";
const std::string LIFE_STR = "life";

const int SPEED_INDEX = 1;
const int MASS_INDEX = 3;
const int SIZE_INDEX = 0;
const int LIFE_INDEX = 1;


/************************************WEAPON CONFIG*******************************/

const std::string DAMAGE_STR = "damage";
const std::string COOLDOWN_STR = "cooldown";
const std::string AMMO_STR = "ammo";
const std::string SCOPE_STR = "scope";

const std::string NONE_STR = "none";
const std::string SHORT_STR = "short";
const std::string MINIMUN_STR = "minimun";
const std::string MEDIUM_STR = "medium";
const std::string LONG_STR = "long";
const std::string TO_EXPLOTE_GRANADE_STR = "to_explote_granade";
const std::string COLLECTABLE_TYPES_STR = "collectable_types";
const std::string EMPTY_STR = "empty";
const std::string HELMET_STR = "helmet";
const std::string ARMOR_STR = "armor";
const std::string BASIC_STR = "basic";

const std::string SHO0TING_INCLINATION_STR = "shooting_inclination";
const std::string PROJECTILE_PER_SHOT_STR = "projectiles_per_shot";
const std::string COLLECTABLE_STR = "collectable";


/****************************DISPERSION****************************************/
const std::string DISPERSION_STR = "dispersion";
const std::string NO_DISPERSION_STR = "no_dispersion";
const std::string SUPER_DISPERSION = "super";
const std::string HIPER_DISPERSION = "hiper";
/****************************WEAPONS*******************************************/
const std::string BANANA_STR = "banana";
const std::string LASER_RIFLE_STR = "laser_rifle";
const std::string COWBOY_PISTOL_STR = "cowboy_pistol";
const std::string GRANADE_STR = "granade";
const std::string MANGUM_STR = "magnum";
const std::string SHOTGUN_STR = "shotgun";
const std::string SNIPER_STR = "sniper";
const std::string AK47_STR = "ak47";
const std::string DUELING_PISTOL_STR = "dueling_pistol";
const std::string PEW_PEW_LASER_STR = "pew_pew_laser";
const std::string BOX_STR = "box";
const std::string TIME_STR = "time";

const int BANANA_INDEX = 0;
const int LASER_RIFLE_INDEX = 1;
const int GRANADE_INDEX = 2;
const int COWBOY_PISTOL_INDEX = 3;
const int AK47_INDEX = 4;
const int DUELING_PISTOL_INDEX = 5;
const int MAGNUM_INDEX = 6;
const int SHOTGUN_INDEX = 7;
const int SNIPER_INDEX = 8;
const int PEW_PEW_LASER_INDEX = 9;
const int HELMET_INDEX = 9;
const int ARMOR_INDEX = 10;
const int EMPTY_INDEX = 11;

/***********************************INDEX VECTORS CONFIG******************************/
const int AMMO_INDEX = 0;
const int NONE_INDEX = 0;
const int MINIMUN_INDEX = 0;
const int SCOPE_INDEX = 1;
const int SHORT_INDEX = 1;
const int BOX_INDEX = 1;
const int PRECISION_INDEX = 2;
const int LONG_INDEX = 2;
const int MEDIUM_INDEX = 3;
const int BASIC_INDEX = 4;
const int TO_EXPLOTE_GRANADA_INDEX = 5;
const int SUPER_INDEX = 3;
const int HIPER_INDEX = 4;
const int TIME_INDEX = 1;


/***********************************PATHS**************************************** */
const std::string WEAPONS_PATH = "/etc/duckGame_g6/weaponConfig.yaml";
const std::string MATCH_PATH = "/etc/duckGame_g6/matchConfig.yaml";
const std::string DUCK_PATH = "/etc/duckGame_g6/duckConfig.yaml";
const std::string OBJECT_PATH = "/etc/duckGame_g6/objectConfig.yaml";
const std::string THEME_PATH = "/etc/duckGame_g6/map_themes.yaml";
#endif
