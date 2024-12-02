#include "FontCache.h"

Font& FontCache::GetFontData(const string& filename, int fontSize) {
    string key = filename + "_" + std::to_string(fontSize);

    if (mapCache.contains(key)) {
        return mapCache.at(key);
    }

    mapCache.emplace(key, Font(FONT_PATH + filename, fontSize));
    return mapCache.at(key);
}


void FontCache::Clear() { mapCache.clear(); }
