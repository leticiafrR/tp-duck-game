#include "mapEditor.h"

#include <filesystem>
#include <set>

#include "common/Collision.h"
#include "common/Transform.h"
#include "common/Vector2D.h"

MapEditor::MapEditor(): config(YAML::Node(YAML::NodeType::Map)), platformsCounter(0) {
    config[THEME_STR] = FOREST_KEY;
    config[FULL_MAP_STR][X_STR] = 100;
    config[FULL_MAP_STR][Y_STR] = 160;
    config[PLATFORMS_STR] = YAML::Node(YAML::NodeType::Sequence);
}
MapEditor::MapEditor(const string& _fileName):
        config(YAML::LoadFile(RELATIVE_LEVEL_PATH + _fileName + YAML_FILE)),
        platformsCounter(0),
        fileName(_fileName),
        filePath(RELATIVE_LEVEL_PATH + _fileName + YAML_FILE) {

    if (config[PLATFORMS_STR] && config[PLATFORMS_STR].IsSequence()) {
        platformsCounter = config[PLATFORMS_STR].size();
    } else {
        config[PLATFORMS_STR] = YAML::Node(YAML::NodeType::Sequence);
    }
}
void MapEditor::SaveChanges() {
    std::ofstream fout(filePath);
    if (!fout.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << filePath << std::endl;
        return;
    }
    fout << config;

    fout.close();
    YAML::Node availableConfig;
    try {
        availableConfig = YAML::LoadFile(AVAILABLE_LEVELS_PATH);
    } catch (const YAML::Exception& e) {
        std::cerr << "Error loading available levels file:" << e.what() << std::endl;
        return;
    }
    std::vector<std::string> availableLevels;
    try {
        availableLevels = availableConfig[AVAILABLE_LEVELS_STR].as<std::vector<std::string>>();
    } catch (const YAML::Exception& e) {
        std::cerr << "Error reading available levels:" << e.what() << std::endl;
        return;
    }
    auto it = std::find(availableLevels.begin(), availableLevels.end(), fileName);
    if (it == availableLevels.end()) {
        availableLevels.emplace_back(fileName);
        availableConfig[AVAILABLE_LEVELS_STR] = availableLevels;
        std::ofstream fout2(AVAILABLE_LEVELS_PATH);
        if (!fout2.is_open()) {
            std::cerr << "Error: Could not open file for writing: " << AVAILABLE_LEVELS_PATH
                      << std::endl;
            return;
        }
        fout2 << availableConfig;
        fout2.close();
    }
}
optional<GroundDto> MapEditor::TakePltaform(const Vector2D pos) {
    vector<string> platforms = config[PLATFORMS_STR].as<vector<string>>();
    for (const auto& name: platforms) {
        float x = config[name][X_STR].as<float>();
        float y = config[name][Y_STR].as<float>();
        float w = config[name][WEIGHT_STR].as<float>();
        float h = config[name][HIGH_STR].as<float>();
        vector<string> edgesConfig = config[name][EDGES_STR].as<vector<string>>();
        set<VISIBLE_EDGES> edges;
        for (auto edge: edgesConfig) {
            if (edge == LEFT_STR)
                edges.insert(LEFT);
            else if (edge == RIGHT_STR)
                edges.insert(RIGHT);
            else if (edge == TOP_STR)
                edges.insert(TOP);
            else if (edge == BOTTOM_STR)
                edges.insert(BOTTOM);
        }

        GroundDto platform(Transform(Vector2D(x, y), Vector2D(w, h), NULL_ANGLE), edges);
        if (Collision::RectCollision(platform.mySpace, Transform(pos, Vector2D(2, 2), 0))) {
            DeleteAPlatform(name);
            return platform;
        }
    }
    return std::nullopt;
}
void MapEditor::AddFileName(const string& _fileName) {
    fileName = _fileName;
    filePath = RELATIVE_LEVEL_PATH + fileName + YAML_FILE;
}
void MapEditor::AddAPlataform(const float& x, const float& y, const float& w, const float& h,
                              const vector<string>& edges) {

    if (w >= MINIMUN_SIZE && h >= MINIMUN_SIZE) {
        YAML::Node platform = YAML::Node(YAML::NodeType::Map);
        platform[X_STR] = x;
        platform[Y_STR] = y;
        platform[WEIGHT_STR] = w;
        platform[HIGH_STR] = h;
        platform[EDGES_STR] = edges;
        string platformName = PLATFORM_KEY + std::to_string(platformsCounter++);
        config[platformName] = platform;
        config[PLATFORMS_STR].push_back(platformName);
    }
}
void MapEditor::AddPlayerSpawnPoint(const float& x, const float& y) {
    YAML::Node playersSpawnPoint = YAML::Node(YAML::NodeType::Map);
    playersSpawnPoint[X_STR] = x;
    playersSpawnPoint[Y_STR] = y;
    if (!config[PLAYERS_POINTS_STR]) {
        config[PLAYERS_POINTS_STR] = YAML::Node(YAML::NodeType::Sequence);
    }
    config[PLAYERS_POINTS_STR].push_back(playersSpawnPoint);
}
void MapEditor::AddCollectableSpawnPoint(const float& x, const float& y) {
    YAML::Node weaponSpawnPoint = YAML::Node(YAML::NodeType::Map);
    weaponSpawnPoint[X_STR] = x;
    weaponSpawnPoint[Y_STR] = y;
    if (!config[COLLECTABLE_POINTS_STR]) {
        config[COLLECTABLE_POINTS_STR] = YAML::Node(YAML::NodeType::Sequence);
    }
    config[COLLECTABLE_POINTS_STR].push_back(weaponSpawnPoint);
}

void MapEditor::AddTheme(const string& theme) { config[THEME_STR] = theme; }
void MapEditor::AddFullMapSize(const size_t& x, const size_t& y) {
    config[FULL_MAP_STR][X_STR] = x;
    config[FULL_MAP_STR][Y_STR] = y;
}
void MapEditor::DeleteALevel() {
    if (remove(filePath.c_str()) != 0) {
        std::cerr << "Occurred an error when trying to delete the file: " << filePath << std::endl;
    } else {
        YAML::Node availableConfig = YAML::LoadFile(AVAILABLE_LEVELS_PATH);
        vector<string> availableLevels = availableConfig[AVAILABLE_LEVELS_STR].as<vector<string>>();
        auto it = find(availableLevels.begin(), availableLevels.end(), filePath);
        if (it != availableLevels.end()) {
            availableLevels.erase(it);
            availableConfig[AVAILABLE_LEVELS_STR] = availableLevels;
            std::ofstream foutAvailable(AVAILABLE_LEVELS_PATH);
            foutAvailable << availableConfig;
        }
    }
}
void MapEditor::ModificateAPlataform(const string& plataformName, const float& x, const float& y,
                                     const float& w, const float& h, const vector<string>& edges) {
    config[plataformName][X_STR] = x;
    config[plataformName][Y_STR] = y;
    config[plataformName][WEIGHT_STR] = w;
    config[plataformName][HIGH_STR] = h;
    config[plataformName][EDGES_STR] = edges;
}
void MapEditor::DeleteAPlatform(const string& platformName) {
    if (config[platformName]) {
        config.remove(platformName);
        vector<string> platforms = config[PLATFORMS_STR].as<vector<string>>();
        for (size_t i = 0; i < platforms.size(); ++i) {
            if (platforms[i] == platformName) {
                platforms.erase(platforms.begin() + i);
                break;
            }
        }
        config[PLATFORMS_STR] = platforms;
    } else {
        std::cerr << "Platform " << platformName << " does not exist in the configuration."
                  << std::endl;
    }
}
vector<GroundDto> MapEditor::GetPlatforms() {
    vector<GroundDto> grounds;
    vector<string> platforms = config[PLATFORMS_STR].as<vector<string>>();
    for (const auto& name: platforms) {
        float x = config[name][X_STR].as<float>();
        float y = config[name][Y_STR].as<float>();
        float w = config[name][WEIGHT_STR].as<float>();
        float h = config[name][HIGH_STR].as<float>();
        vector<string> edgesConfig = config[name][EDGES_STR].as<vector<string>>();
        set<VISIBLE_EDGES> edges;
        for (auto edge: edgesConfig) {
            if (edge == LEFT_STR)
                edges.insert(LEFT);
            else if (edge == RIGHT_STR)
                edges.insert(RIGHT);
            else if (edge == TOP_STR)
                edges.insert(TOP);
            else if (edge == BOTTOM_STR)
                edges.insert(BOTTOM);
        }
        grounds.emplace_back(
                GroundDto(Transform(Vector2D(x, y), Vector2D(w, h), NULL_ANGLE), edges));
    }
    return grounds;
}
GameSceneDto MapEditor::GetGameScene() {
    return GameSceneDto(config[THEME_STR].as<string>(), GetPlatforms(), GetBoxes());
}
unordered_map<BoxID_t, Vector2D> MapEditor::GetBoxes() {
    BoxID_t id = 0;
    unordered_map<BoxID_t, Vector2D> boxes;
    auto _boxSpawnPoints = config[BOX_POINTS_STR];
    for (std::size_t i = 0; i < _boxSpawnPoints.size(); ++i) {
        Vector2D pos;
        pos.x = _boxSpawnPoints[i][X_STR].as<float>();
        pos.y = _boxSpawnPoints[i][Y_STR].as<float>();
        boxes[id] = pos;
    }
    return boxes;
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
