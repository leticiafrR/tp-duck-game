#include "FontCache.h"

map<string, Font> FontCache::cache;

Font& FontCache::GetData(const string& filename, int fontSize) {
    string key = filename + "_" + std::to_string(fontSize);

    auto it = cache.find(key);
    if (it != cache.end()) {
        return it->second;
    }

    cache.emplace(key, Font(FONT_PATH + filename, fontSize));
    return cache.at(key);
}

const Font& FontCache::GetFontData(const string& filename, int fontSize) {
    string key = filename + "_" + std::to_string(fontSize);

    if (mapCache.contains(key)) {
        return mapCache.at(key);
    }

    mapCache.emplace(key, Font(FONT_PATH + filename, fontSize));
    return mapCache.at(key);
}


void FontCache::Clear() { cache.clear(); }
