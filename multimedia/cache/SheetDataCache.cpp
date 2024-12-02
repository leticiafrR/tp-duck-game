#include "SheetDataCache.h"

unordered_map<string, vector<Rect>> SheetDataCache::GetData(const string& filename) {
    auto it = cache.find(filename);
    if (it != cache.end()) {
        return it->second;
    }

    YAML::Node yamlData = YAML::LoadFile(SHEET_DATA_PATH + filename);

    unordered_map<string, vector<Rect>> data;

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

void SheetDataCache::Clear() { cache.clear(); }
unordered_map<string, unordered_map<string, vector<Rect>>> SheetDataCache::cache;
