#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <optional>
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "multimedia/Definitions.h"
#include "multimedia/cache/YamlDataCache.h"

#include "ResourceConstants.h"
#include "ResourceData.h"
#include "ResourceParser.h"

using namespace SDL2pp;  // NOLINT
using std::optional;
using std::string;
using std::unordered_map;

struct ResourceUndefined: public std::runtime_error {
    ResourceUndefined(): std::runtime_error("The resource required is not defined") {}
};

class ResourceManager {
private:
    YamlDataCache dataCache;
    YAML::Node root;

    unordered_map<TypeItem, CollectableData> collectablesMap;
    unordered_map<TypeProjectile, ProjectileData> projectilesMap;

    optional<DuckData> duckData = std::nullopt;
    optional<ArmorData> armorData = std::nullopt;

    optional<MenuData> menuData = std::nullopt;

    unordered_map<string, MapThemeData> mapThemesData;

public:
    ResourceManager();
    ~ResourceManager();

    const MenuData& GetMenuData();

    const DuckData& GetDuckData();

    MapThemeData& GetMapThemeData(string theme);

    const ArmorData& GetArmorData();

    CollectableData GetCollectableData(TypeItem type);

    ProjectileData GetProjectilData(TypeProjectile type);

    void LoadMapThemesData();

    void LoadCollectablesData();
    void LoadProjectilesData();
};

#endif
