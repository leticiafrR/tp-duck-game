#include "YamlDataCache.h"

const YAML::Node& YamlDataCache::GetData(const std::string& fileName) {
    if (mapCache.contains(fileName)) {
        return mapCache.at(fileName);
    }

    YAML::Node node = YAML::LoadFile(fileName);
    mapCache[fileName] = node;
    return mapCache.at(fileName);
}
