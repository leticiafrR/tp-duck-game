#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

using std::string;

const int SUCCESS_SHUTDOWN = 2;
const int FAILURE_SHUTDOWN = 1;

const int SUCCESS_EXIT = 0;
const int FAILURE_EXIT = 1;

/***************************YAML FILES******************************* */
const string THEME_STR = "theme";
const string FULL_MAP_STR = "full_map_size";
const string X_STR = "x";
const string Y_STR = "y";
const string PLAYERS_POINTS_STR = "players_spawn_points";
const string COLLECTABLE_POINTS_STR = "collectable_spawn_points";
const string BOX_POINTS_STR = "box_spawn_points";
const string PLATFORMS_STR = "platforms";
const string EDGES_STR = "edges";
const string WEIGHT_STR = "w";
const string HIGH_STR = "h";
const string LEFT_STR = "LEFT";
const string RIGHT_STR = "RIGHT";
const string BOTTOM_STR = "BOTTOM";
const string TOP_STR = "TOP";
const string KEY = "key";
const std::string RELATIVE_LEVEL_PATH = "/etc/duckGame_g6/levels/";
const std::string YAML_FILE = ".yaml";

/*************************CONFIG YAML**********************************/
const string AVAILABLE_LEVELS_STR = "available_levels";
const string MAX_PLAYERS_STR = "max_players";
const string MIN_PLAYERS_STR = "min_players";
const string GAMES_TO_WIN_STR = "game_to_win_match";
const string GAMES_IN_GROUP = "games_in_group";

const string AVAILABLE_LEVELS_PATH = "/etc/duckGame_g6/availableLevels.yaml";


/*********************ASSETS FILES NAMES **************************** */
const string BUTTON_IMAGE_PATH = "button_0.png";
const string DUCK_BACKGROUND = "duck_game_bg.jpg";
const string DUCK_GAME_LOGO = "duck_game_logo.png";
const string BUTTON_1_IMAGE = "button_1.png";
const string BLOCK_MAP = "tile_set.png";
const string BLOCK_MAP_YAML = "tile_set.yaml";
const string WHITE_DUCK = "white_duck.png";
const string BOX_IMG = "box.jpg";
const string TILE_KEY = "tile_set_file";
const string FOREST_KEY = "FOREST";
const string TILE_DATA_KEY = "tile_data";
const string AVAILABLE_THEMES_PATH = "themes.yaml";
const string BACKGROUND_KEY = "bg_file";

const string THEME_PATH = "/etc/duckGame_g6/map_themes.yaml";
const int PLAYERS_SPAWN_POINT = 0;
const int COLLECTABLE_SPAWN_POINT = 1;
const int BOX_SPAWN_POINT = 2;
#endif
