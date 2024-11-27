#ifndef SHEET_DATA_CACHE_H
#define SHEET_DATA_CACHE_H

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include <SDL2pp/SDL2pp.hh>
#include <yaml-cpp/yaml.h>

#include "multimedia/Definitions.h"

using SDL2pp::Rect;
using std::map;
using std::string;
using std::vector;

class SheetDataCache {
private:
    static map<string, map<string, vector<Rect>>> cache;

public:
    SheetDataCache() = delete;
    ~SheetDataCache() = delete;

    static map<string, vector<Rect>> GetData(const string& filename);

    static void Clear();
};

#endif
