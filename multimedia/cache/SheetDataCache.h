#ifndef SHEET_DATA_CACHE_H
#define SHEET_DATA_CACHE_H

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2pp/SDL2pp.hh>
#include <yaml-cpp/yaml.h>

#include "multimedia/Definitions.h"

using SDL2pp::Rect;
using std::string;
using std::unordered_map;
using std::vector;

class SheetDataCache {
private:
    static unordered_map<string, unordered_map<string, vector<Rect>>> cache;

public:
    SheetDataCache() = delete;
    ~SheetDataCache() = delete;

    static unordered_map<string, vector<Rect>> GetData(const string& filename);

    static void Clear();
};

#endif
