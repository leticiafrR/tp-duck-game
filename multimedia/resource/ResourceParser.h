#ifndef RESOURCE_PARSER_H
#define RESOURCE_PARSER_H

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "ResourceConstants.h"
#include "ResourceData.h"

using std::string;
using std::unordered_map;
using std::vector;

class ResourceParser {
private:
public:
    ResourceParser() = delete;
    ~ResourceParser() = delete;

    static MenuData ParseMenu(YAML::Node data);
    static MapThemeData ParseMapThemeData(YAML::Node data);

    static DuckData ParseDuck(YAML::Node data);
    static ArmorData ParseArmor(YAML::Node data);

    static CollectableData ParseCollectable(YAML::Node itemData);
    static ProjectileData ParseProjectil(YAML::Node itemData);
};

#endif
