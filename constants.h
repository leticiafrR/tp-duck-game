#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

const int SUCCESS_SHUTDOWN = 2;
const int FAILURE_SHUTDOWN = 1;

const int SUCCESS_EXIT = 0;
const int FAILURE_EXIT = 1;

/***************************YAML FILES******************************* */
const std::string THEME_STR = "theme";
const std::string FULL_MAP_STR = "full_map_size";
const std::string X_STR = "x";
const std::string Y_STR = "y";
const std::string PLAYERS_POINTS_STR = "players_spawn_points";
const std::string WEAPONS_POINTS_STR = "weapons_spawn_points";
const std::string BOX_POINTS_STR = "box_spawn_points";
const std::string PLATFORMS_STR = "platforms";
const std::string EDGES_STR = "edges";
const std::string WEIGHT_STR = "w";
const std::string HIGH_STR = "h";
const std::string LEFT_STR = "LEFT";
const std::string RIGHT_STR = "RIGHT";
const std::string BOTTOM_STR = "BOTTOM";
const std::string TOP_STR = "TOP";

const std::string RELATIVE_LEVEL_PATH = "../config/levels/";
const std::string YAML_FILE = ".yaml";

/**************************************CONFIG YAML****************************************/
const std::string AVAILABLE_LEVELS_STR = "available_levels";
const std::string MAX_PLAYERS_STR = "max_players";
const std::string MIN_PLAYERS_STR = "min_players";
const std::string GAMES_TO_WIN_STR = "game_to_win_match";
const std::string GAMES_IN_GROUP = "games_in_group";

const std::string AVAILABLE_LEVELS_PATH = "../config/availableLevels.yaml";
#endif
