#ifndef RESOURCE_DATA_H
#define RESOURCE_DATA_H

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "ResourceConstants.h"

using namespace SDL2pp;  // NOLINT
using std::unordered_map;
using std::vector;

class ItemData {
public:
    string file;
    Rect rect;
    Vector2D size;
};

class CollectableData: public ItemData {
public:
    float angle;
};

class ProjectileData: public ItemData {
public:
    string sfxFile;
    float speed;
};


class DuckData {
public:
    string file;
    string cuackFileSFX;
    string damagedFileSFX;
    unordered_map<string, vector<Rect>> frames;
};

class ArmorData {
public:
    string file;
    unordered_map<string, vector<Rect>> frames;
};

class MenuData {
public:
    string menuBgFile;
    string logoBgFile;
    string buttonImgFile;
    string buttonBackImgFile;
    string buttonSfxFile;
};

class MapThemeData {
public:
    string bgfile;
    string bgMusicFile;
    string tileSetFile;

    unordered_map<string, vector<Rect>> tileRects;
};


#endif
