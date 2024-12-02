#ifndef CONSTANTSEDITOR_H
#define CONSTANTSEDITOR_H
#include <string>
using std::string;
// file
const string PLATFORM_KEY = "platform_";
const float MINIMUN_SIZE = 8;
const float NULL_ANGLE = 0;

const string WINDOW_LABEL = "Levels Editor Duck Game";
const string PIXEL_FONT = "../assets/fonts/pixel.ttf";
const string CREATE_LABEL = "Create a level";
const string EDIT_LABEL = "Edit a level";

const string SELECT_STR = "Select";
const string ENTER_LVL_NAME = "Write the level name";
const string SAVE_LABEL = "Save";
const string EXIT_LABEL = "Exit";
const string MENU_LABEL = "Menu options";
const string PLAYER_POINT_LABEL = "Player Points";
const string COLLECTABLE_POINT_LABEL = "Collectables";
const string OPTIONS_BLOCKS = "/etc/duckGame_g6/basicsGrounds.yaml";

const int CREATE_LVL = 0;
const int QUIT = -1;
const int EDIT_LVL = 1;


#endif
