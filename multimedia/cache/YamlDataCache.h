#ifndef YAML_DATA_CACHE_H
#define YAML_DATA_CACHE_H

#include <string>
#include <unordered_map>

#include <yaml-cpp/yaml.h>

class YamlDataCache {
private:
    std::unordered_map<std::string, YAML::Node> mapCache;

public:
    const YAML::Node& GetData(const std::string& fileName);
};

#endif
