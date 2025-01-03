#include "ResourceManager.h"

ResourceManager::ResourceManager(): root(YAML::LoadFile(RESOURCE_DATA_PATH + RESOURCE_ROOT)) {}
ResourceManager::~ResourceManager() = default;

AudioCache& ResourceManager::GetAudioCache() { return audioCache; }

const MenuData& ResourceManager::GetMenuData() {
    if (!menuData.has_value()) {
        auto dataNode = YAML::LoadFile(RESOURCE_DATA_PATH + root["menu"].as<std::string>());
        menuData = ResourceParser::ParseMenu(dataNode);
    }
    return menuData.value();
}

const DuckData& ResourceManager::GetDuckData() {
    if (!duckData.has_value()) {
        auto dataNode = YAML::LoadFile(RESOURCE_DATA_PATH + root["duck"].as<std::string>());
        duckData = ResourceParser::ParseDuck(dataNode);
    }
    return duckData.value();
}

MapThemeData& ResourceManager::GetMapThemeData(string theme) {
    if (mapThemesData.size() == 0) {
        LoadMapThemesData();
    }

    if (!mapThemesData.contains(theme)) {
        std::cerr << "Undefined theme resource: " << theme << "\n";
        throw ResourceUndefined();
    }

    return mapThemesData.at(theme);
}

const ArmorData& ResourceManager::GetArmorData() {
    if (!armorData.has_value()) {
        auto dataNode = YAML::LoadFile(RESOURCE_DATA_PATH + root["armor"].as<std::string>());
        armorData = ResourceParser::ParseArmor(dataNode);
    }
    return armorData.value();
}

CollectableData ResourceManager::GetCollectableData(TypeItem type) {
    if (collectablesMap.size() == 0) {
        LoadCollectablesData();
    }

    if (!collectablesMap.contains(type)) {
        std::cerr << "Undefined collectable resource: " << (int)type << "\n";
        throw ResourceUndefined();
    }

    return collectablesMap.at(type);
}

ProjectileData ResourceManager::GetProjectilData(TypeProjectile type) {
    if (projectilesMap.size() == 0) {
        LoadProjectilesData();
    }

    if (!projectilesMap.contains(type)) {
        std::cerr << "Undefined projectile resource: " << (int)type << "\n";
        throw ResourceUndefined();
    }

    return projectilesMap.at(type);
}

void ResourceManager::LoadMapThemesData() {
    YAML::Node themesNode =
            YAML::LoadFile(RESOURCE_DATA_PATH + root["map_themes"].as<std::string>());

    for (const auto& itemData: themesNode) {
        const string key = itemData.first.as<string>();

        mapThemesData[key] = ResourceParser::ParseMapThemeData(itemData.second);
    }
}

void ResourceManager::LoadCollectablesData() {
    YAML::Node collectablesNode =
            YAML::LoadFile(RESOURCE_DATA_PATH + root["collectables"].as<std::string>());

    for (const auto& itemData: collectablesNode) {
        const string key = itemData.first.as<string>();

        if (!COLLECTABLES.contains(key))
            continue;

        collectablesMap[COLLECTABLES.at(key)] = ResourceParser::ParseCollectable(itemData.second);
    }
}

void ResourceManager::LoadProjectilesData() {
    YAML::Node projectilesNode =
            YAML::LoadFile(RESOURCE_DATA_PATH + root["projectiles"].as<std::string>());

    for (const auto& itemData: projectilesNode) {
        const string key = itemData.first.as<string>();

        if (!PROJECTILES.contains(key))
            continue;

        projectilesMap[PROJECTILES.at(key)] = ResourceParser::ParseProjectil(itemData.second);
    }
}
