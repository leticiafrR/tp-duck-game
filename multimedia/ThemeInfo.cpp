#include "ThemeInfo.h"

#include "constants.h"

ThemeInfo::ThemeInfo(): config(YAML::LoadFile(THEME_PATH)) {}

string ThemeInfo::GetBackgroundPath(const string& key) {
    return config[key][BACKGROUND_KEY].as<string>();
}

string ThemeInfo::GetTileDataPath(const string& key) {
    return config[key][TILE_DATA_KEY].as<string>();
}

string ThemeInfo::GetTilePath(const string& key) { return config[key][TILE_KEY].as<string>(); }
