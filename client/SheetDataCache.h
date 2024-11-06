#ifndef SHEET_DATA_CACHE_H
#define SHEET_DATA_CACHE_H

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include <SDL2pp/SDL2pp.hh>
#include <yaml-cpp/yaml.h>

using SDL2pp::Rect;
using std::map;
using std::string;
using std::vector;

#define SHEET_DATA_PATH "../client/assets/sheet_data/"

class SheetDataCache {
private:
    static map<string, map<string, vector<Rect>>> cache;

public:
    SheetDataCache() = delete;
    ~SheetDataCache() = delete;

    static map<string, vector<Rect>> GetData(string filename) {
        auto it = cache.find(filename);
        if (it != cache.end()) {
            return it->second;
        }

        YAML::Node yamlData = YAML::LoadFile(SHEET_DATA_PATH + filename);

        map<string, vector<Rect>> data;

        for (const auto& item: yamlData) {
            const string key = item.first.as<string>();

            vector<Rect> rects;
            std::transform(item.second.begin(), item.second.end(), std::back_inserter(rects),
                           [](const YAML::Node& rectItem) {
                               return Rect(rectItem["x"].as<int>(), rectItem["y"].as<int>(),
                                           rectItem["w"].as<int>(), rectItem["h"].as<int>());
                           });

            data[key] = rects;
        }
        cache[filename] = data;
        return data;
    }

    static void Clear() { cache.clear(); }
};
map<string, map<string, vector<Rect>>> SheetDataCache::cache;

#endif
