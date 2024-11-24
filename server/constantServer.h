#ifndef CONSTANTSERVER_H
#define CONSTANTSERVER_H

#include <string>

/************************************STATIC MAP YAML*************************************/
const std::string THEME_STR = "theme";
const std::string FULL_MAP_STR = "full_map_size";
const std::string X_STR = "x";
const std::string Y_STR = "y";
const std::string PLAYERS_POINTS_STR = "players_spawn_points";
const std::string PLATAFORM_STR = "plataforms";
const std::string EDGES_STR = "edges";
const std::string WEIGHT_STR = "w";
const std::string HIGH_STR = "h";
const std::string LEFT_STR = "LEFT";
const std::string RIGHT_STR = "RIGHT";
const std::string BOTTOM_STR = "BOTTOM";
const std::string TOP_STR = "TOP";

const float HALF = 2;
const float FALLING = -1;

/**************************************CONFIG YAML****************************************/
const std::string AVAIABLE_LEVELS_STR = "avaiable_levels";
const std::string MAX_PLAYERS_STR = "max_players";
const std::string MIN_PLAYERS_STR = "min_players";
const std::string GAMES_TO_WIN_STR = "game_to_win_match";
const std::string GAMES_IN_GROUP = "games_in_group";


/****************************************DUCK CONFIG***************************************/
const std::string SPEED_STR = "speed";
const std::string MASS_STR = "mass";
const std::string SIZE_STR = "size";
const std::string LIFE_STR = "life";

const int SPEED_INDEX = 0;
const int MASS_INDEX = 1;
const int SIZE_INDEX = 2;
const int LIFE_INDEX = 3;

/************************************WEAPON CONFIG****************************************/

const std::string DAMAGE_STR = "damage";
const std::string COOLDOWN_STR = "cooldown";
const std::string AMMO_STR = "ammo";
const std::string SCOPE_STR = "scope";

const std::string NONE_STR = "none";
const std::string SHORT_STR = "short";
const std::string MINIMUN_STR = "minimun";
const std::string MEDIUM_STR = "medium";
const std::string LONG_STR = "long";
const std::string TO_EXPLOTE_GRANADA_STR = "to_explote_granada";
const std::string COLLECTABLE_TYPES_STR = "collectable_types";
const std::string EMPTY_STR = "empty";
const std::string HELMET_STR = "helmet";
const std::string ARMOR_STR = "armor";
const std::string BASIC_STR = "basic";
/****************************DISPERSION************************************* */
const std::string DISPERSION_STR = "dispersion";
const std::string NO_DISPERSION_STR = "no_dispersion";
// Weapons
const std::string BANANA_STR = "banana";
const std::string LASER_RIFLE_STR = "laser_rifle";
const std::string COWBOY_PISTOL_STR = "cowboy_pistol";
const std::string GRANADA_STR = "granada";
const std::string MANGUM_STR = "magnum";
const std::string SHOTGUN_STR = "shotgun";
const std::string SNIPER_STR = "sniper";
const std::string AK47_STR = "ak47";

const int BANANA_INDEX = 0;
const int GRANADA_INDEX = 1;
const int LASER_RIFLE_INDEX = 2;
const int COWBOY_PISTOL_INDEX = 3;
const int AK47_INDEX = 4;
const int DUELING_PISTOL_INDEX = 5;
const int MAGNUM_INDEX = 6;
const int SHOTGUN_INDEX = 7;
const int SNIPER_INDEX = 8;
const int HELMET_INDEX = 9;
const int ARMOR_INDEX = 10;
const int EMPTY_INDEX = 11;

/***********************************INDEX VECTORS CONFIG*******************************************/
const int AMMO_INDEX = 0;
const int SCOPE_INDEX = 1;
const int PRECISION_INDEX = 2;
const int MINIMUN_INDEX = 0;
const int SHORT_INDEX = 1;
const int MEDIUM_INDEX = 3;
const int LONG_INDEX = 2;
const int NONE_INDEX = 0;
const int TO_EXPLOTE_GRANADA_INDEX = 5;
const int BASIC_INDEX = 4;

#endif