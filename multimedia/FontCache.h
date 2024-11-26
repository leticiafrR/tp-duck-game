#ifndef FONT_CACHE_H
#define FONT_CACHE_H

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include <SDL2pp/SDL2pp.hh>
#include <yaml-cpp/yaml.h>

#include "Definitions.h"

using namespace SDL2pp;  // NOLINT
using std::map;
using std::string;
using std::vector;

class FontCache {
private:
    static map<string, Font> cache;

public:
    FontCache() = delete;
    ~FontCache() = delete;

    static Font& GetData(const string& filename, int fontSize) {
        string key = filename + "_" + std::to_string(fontSize);

        auto it = cache.find(key);
        if (it != cache.end()) {
            return it->second;
        }

        cache.emplace(key, Font(FONT_PATH + filename, fontSize));
        return cache.at(key);
    }

    static void Clear() { cache.clear(); }
};
map<string, Font> FontCache::cache;

#endif
