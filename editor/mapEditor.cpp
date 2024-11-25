#include "mapEditor.h"

MapEditor::MapEditor(): config(), plataformsCounter(0) {
    config[THEME_STR] = "FOREST";
    config[FULL_MAP_STR][X_STR] = 100;
    config[FULL_MAP_STR][Y_STR] = 160;
}

MapEditor::MapEditor(const std::string& filePath):
        config(filePath), plataformsCounter(0), filePath(filePath) {

    plataformsCounter = config[PLATAFORMS_STR].as<std::vector<std::string>>().size();
}

void MapEditor::SaveChanges() {

    std::ofstream fout(filePath);
    fout << config;

    YAML::Node availableConfig = YAML::LoadFile(AVAILABLE_LEVELS_PATH);
    std::vector<std::string> availableLevels =
            availableConfig[AVAILABLE_LEVELS_STR].as<std::vector<std::string>>();

    auto it = std::find(availableLevels.begin(), availableLevels.end(), filePath);
    if (it == availableLevels.end()) {
        availableLevels.emplace_back(filePath);
        availableConfig[AVAILABLE_LEVELS_STR] = availableLevels;
        std::ofstream fout2(AVAILABLE_LEVELS_PATH);
        fout2 << availableConfig;
    }
}

void MapEditor::AddFileName(const std::string& _fileName) {
    filePath = RELATIVE_LEVEL_PATH + _fileName + YAML_FILE;
}

void MapEditor::AddAPlataform(const float& x, const float& y, const float& w, const float& h,
                              const std::vector<std::string>& edges) {
    YAML::Node platform = YAML::Node(YAML::NodeType::Map);
    platform[X_STR] = x;
    platform[Y_STR] = y;
    platform[WEIGHT_STR] = w;
    platform[HIGH_STR] = h;
    platform[EDGES_STR] = edges;
    std::string platformName = PLATAFORM_KEY + std::to_string(plataformsCounter++);
    config[platformName] = platform;
    config[PLATAFORMS_STR].push_back(platformName);
}

void MapEditor::AddPlayerSpawnPoint(const float& x, const float& y) {
    YAML::Node playersSpawnPoints = YAML::Node(YAML::NodeType::Sequence);
    playersSpawnPoints.push_back(YAML::Node(YAML::NodeType::Map));
    playersSpawnPoints[0][X_STR] = x;
    playersSpawnPoints[0][Y_STR] = y;
    config[PLAYERS_POINTS_STR] = playersSpawnPoints;
}

void MapEditor::AddWeaponSpawnPoint(const float& x, const float& y) {
    YAML::Node weaponSpawnPoint = YAML::Node(YAML::NodeType::Map);
    weaponSpawnPoint[X_STR] = x;
    weaponSpawnPoint[Y_STR] = y;
    if (!config[WEAPONS_POINTS_STR]) {
        config[WEAPONS_POINTS_STR] = YAML::Node(YAML::NodeType::Sequence);
    }
    config[WEAPONS_POINTS_STR].push_back(weaponSpawnPoint);
}

void MapEditor::AddBoxSpawnPoint(const float& x, const float& y) {
    YAML::Node boxSpawnPoint = YAML::Node(YAML::NodeType::Map);
    boxSpawnPoint[X_STR] = x;
    boxSpawnPoint[Y_STR] = y;
    if (!config[BOX_POINTS_STR]) {
        config[BOX_POINTS_STR] = YAML::Node(YAML::NodeType::Sequence);
    }
    config[BOX_POINTS_STR].push_back(boxSpawnPoint);
}

void MapEditor::AddTheme(const std::string& theme) { config[THEME_STR] = theme; }

void MapEditor::AddFullMapSize(const size_t& x, const size_t& y) {
    config[FULL_MAP_STR][X_STR] = x;
    config[FULL_MAP_STR][Y_STR] = y;
}

void MapEditor::DeleteALevel() {
    if (remove(filePath.c_str()) != 0) {
        std::cerr << "Occurred an error when trying to delete the file: " << filePath << std::endl;
    } else {
        YAML::Node availableConfig = YAML::LoadFile(AVAILABLE_LEVELS_PATH);
        std::vector<std::string> availableLevels =
                availableConfig[AVAILABLE_LEVELS_STR].as<std::vector<std::string>>();
        auto it = std::find(availableLevels.begin(), availableLevels.end(), filePath);
        if (it != availableLevels.end()) {
            availableLevels.erase(it);
            availableConfig[AVAILABLE_LEVELS_STR] = availableLevels;
            std::ofstream foutAvailable(AVAILABLE_LEVELS_PATH);
            foutAvailable << availableConfig;
        }
    }
}

void MapEditor::ModificateAPlataform(const std::string& plataformName, const float& x,
                                     const float& y, const float& w, const float& h,
                                     const std::vector<std::string>& edges) {
    config[plataformName][X_STR] = x;
    config[plataformName][Y_STR] = y;
    config[plataformName][WEIGHT_STR] = w;
    config[plataformName][HIGH_STR] = h;
    config[plataformName][EDGES_STR] = edges;
}

void MapEditor::DeleteAPlataform(const std::string& plataformName) {
    if (config[plataformName]) {
        config.remove(plataformName);
        YAML::Node platforms = config[PLATAFORMS_STR];
        for (size_t i = 0; i < platforms.size(); ++i) {
            if (platforms[i].as<std::string>() == plataformName) {
                platforms.remove(i);
                break;
            }
        }
    } else {
        std::cerr << "Platform " << plataformName << " does not exist in the configuration."
                  << std::endl;
    }
}
